#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "lanedetection.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

lanedetection::lanedetection(Mat frame)
{
	this->frame = frame;

	// Region of Interest
	roi_x = 1;
	roi_y = (IMAGEHEIGHT / 2.6);
	roi_width = (IMAGEWIDTH - 2);
	roi_height = (IMAGEHEIGHT / 1.28) - roi_y;
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 640x480 (x=1, y=185, w=638, h=190)
	frame_roi = frame(region_of_interest);

	// Convert to Grayscale
	cvtColor(frame_roi, img_gray, CV_BGR2GRAY);
	// Blur image for less noise
	blur(img_gray, img_edges, cv::Size(3, 3));

	// Edge detection using canny detector
	minCannyThreshold = 50;
	maxCannyThreshold = 3 * minCannyThreshold;
	Canny(img_edges, img_edges, minCannyThreshold, maxCannyThreshold, 3, true);

	// Morphological Operation
	k = getStructuringElement(CV_SHAPE_RECT, Size(9, 9)); // morph_close (9, 9)
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
		
		// WENN Steigung kleiner 0.2, DANN moeglicherweise Linke Fahrspurbegrenzung
		if(steigung < 0.2){
			// Liegen beide Punkte der Linie im linken Bildbereich?
			if(l[0] < (IMAGEWIDTH / 2) && l[2] < (IMAGEWIDTH / 2)) {
				lines_left.push_back(l);
			}
		}
		// WENN Steigung groesser 0.2, DANN moeglicherweise Rechte Fahrspurbegrenzung
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
	
	// Zeichen der Linien mit den Durchschnittswerten
	left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
	right_Color = Scalar(0,0,250);  // B=0 G=0 R=250
	line(frame_roi, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3, CV_AA);
	line(frame_roi, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3, CV_AA);
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
