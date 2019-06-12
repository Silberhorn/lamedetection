#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "lanedetection.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

lanedetection::lanedetection(Mat frame)
{
	this->frame = frame;

	int IMAGEHEIGHT = 480;
	int IMAGEWIDTH = 640;

	// Region of Interest
	roi_x = 1;
	roi_y = (IMAGEHEIGHT / 2.6);
	roi_width = (IMAGEWIDTH - 2);
	roi_height = (IMAGEHEIGHT / 1.28) - roi_y;
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 640x480 (x=1, y=185, w=638, h=190)
	frame_roi = frame(region_of_interest);

	// Convert to Grayscale
	cvtColor(frame_roi, img_gray, COLOR_BGR2GRAY);
	// Blur image for less noise
	blur(img_gray, img_edges, cv::Size(3, 3));

	// Edge detection using canny detector
	minCannyThreshold = 50;
	maxCannyThreshold = 3 * minCannyThreshold;
	Canny(img_edges, img_edges, minCannyThreshold, maxCannyThreshold, 3, true);

	// Morphological Operation
	k = getStructuringElement(MORPH_RECT, Size(9, 9)); // morph_close (9, 9)
	morphologyEx(img_edges, img_edges, MORPH_CLOSE, k);

	// Hough Transform
	rho				= 2;
	theta			= CV_PI / 180;
	threshold_hough	= 30;
	minLinLength	= 110;
	maxLineGap		= 60;

	HoughLinesP(img_edges, lines, rho, theta, threshold_hough, minLinLength, maxLineGap);

	// Differentiate Left and Right Lane
	for(int i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];  // p1=x1,y1  p2=x2,y2

		// Berechnung der Steigung aus dem Punkt mit m = ((y2 - y1) / (x2 -x1))
		steigung = (static_cast<double>(l[3] - l[1]) / static_cast<double>(l[2] - l[0]));

		// WENN Steigung kleiner 0.2, DANN moeglicherweise linke Fahrspurbegrenzung
		if(steigung < 0.2){
			// Liegen beide Punkte der Linie im linken Bildbereich?
			if(l[0] < (IMAGEWIDTH / 2) && l[2] < (IMAGEWIDTH / 2)) {
				lines_left.push_back(l);
			}
		}
		// WENN Steigung groesser 0.2, DANN moeglicherweise rechte Fahrspurbegrenzung
		if(steigung > 0.2){
			// Liegen beide Punkte der Linie im rechten Bildbereich?
			if(l[0] > (IMAGEWIDTH / 2) && l[2] > (IMAGEWIDTH / 2)) {
				lines_right.push_back(l);
			}
		}
	}

	float lane_length_left = 0.0;
	float lane_length_right = 0.0;

	// Finde die Laengste unter den linken Fahrspurbegrenzungen
	for(int i = 0; i < lines_left.size(); i++) {
		Vec4i l = lines_left[i];
		point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
		float d = boost::geometry::distance(p1, p2);

		if(lane_length_left < d) {
			lane_length_left = d;
			left = l;
		}
	}

	// Finde die Laengste unter den rechten Fahrspurbegrenzungen
	for(int i = 0; i < lines_right.size(); i++) {
		Vec4i l = lines_right[i];
		point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
		float d = boost::geometry::distance(p1, p2);
		if(lane_length_right < d) {
			lane_length_right = d;
			right = l;
		}
	}

	if(left[0] == 0 && left[1] == 0 && left[2] == 0 && left[3] == 0) {
		//left[0] = IMAGEWIDTH - right[2];
		//left[1] = right[3];
		//left[2] = IMAGEWIDTH - right[0];
		//left[3] = right[1];

		noLineLeft = true;
	} else {
		noLineLeft = false;
	}

	if(right[0] == 0 && right[1] == 0 && right[2] == 0 && right[3] == 0) {
		//right[0] = IMAGEWIDTH - left[2];
		//right[1] = left[3];
		//right[2] = IMAGEWIDTH - left[0];
		//right[3] = left[1];

		noLineRight = true;
	} else {
		noLineRight = false;
	}

	middle[0] = (left[0] + right[2]) / 2;
	middle[1] = (left[1] + right[3]) / 2;
	middle[2] = (left[2] + right[0]) / 2;
	middle[3] = (left[3] + right[1]) / 2;

	// Zeichen der Linien mit den Durchschnittswerten
	left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
	right_Color = Scalar(0,0,250);  // B=0 G=0 R=250
	middle_Color = Scalar(250,0,0);  // B=250 G=0 R=0
	line(frame_roi, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3);
	line(frame_roi, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3);
	line(frame_roi, Point(middle[0], middle[1]), Point(middle[2], middle[3]), middle_Color, 3);
}

lanedetection::~lanedetection() {}

Mat lanedetection::getEdgeImage()
{
    return img_edges;
}

Mat lanedetection::getLaneImage()
{
	return frame;
}

Vec4i lanedetection::getLeft()
{
	return left;
}

Vec4i lanedetection::getRight()
{
	return right;
}

Vec4i lanedetection::getMiddle()
{
	return middle;
}

int lanedetection::getSteeringAngle()
{
	int8_t steering = 0;
	int middle_point_offset;

	middle_point_offset = ((middle[0] + middle[2]) / 2) - 320;

	// Faktor und Offset
	middle_point_offset = middle_point_offset * 0.28 + 90;	// 0.28

	cout << "Steering: " << middle_point_offset << endl;

	if(middle_point_offset < 0) {
		middle_point_offset = 0;
	}
	if(middle_point_offset > 180) {
		middle_point_offset = 180;
	}

	steering = middle_point_offset;

	return steering;
}

bool lanedetection::getNoLineLeft()
{
	return noLineLeft;
}

bool lanedetection::getNoLineRight()
{
	return noLineRight;
}

double lanedetection::getSteigungLeft()
{
	return (static_cast<double>(left[3] - left[1]) / static_cast<double>(left[2] - left[0]));
}

double lanedetection::getSteigungRight()
{
	return (static_cast<double>(right[3] - right[1]) / static_cast<double>(right[2] - right[0]));
}

double lanedetection::getSteigungMiddle()
{
	return (static_cast<double>(middle[2] - middle[0]) / static_cast<double>(middle[3] - middle[1]));
}