#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "lanedetection.h"
#include "lanecalculation.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

Mat frame_roi;
Mat img_gray;
Mat img_edges;
Mat img_lines;
int roi_x;
int roi_y;
int roi_width;
int roi_height;
Rect region_of_interest;

// Canny
int minCannyThreshold;
int maxCannyThreshold;

// Morphological Operation
Mat k;

// Hough Transform
double rho;
double theta;
int threshold_hough;
double minLinLength;
double maxLineGap;

// Steigungen
double steigung;
double steigung_left;
double y_achsenabschnitt_left;
double x_Schnitt_left;
double steigung_right;
double y_achsenabschnitt_right;
double x_Schnitt_right;

int counter_left;
int counter_right;

// Vektoren für erkannte Koordinaten
vector<Vec4i> lines;
Vec4i left;
Vec4i right;

// Distanz zum Fahrbahnrand
int distance_L;
int distance_R;

// Farbe Fahrbahnmarkierung
Scalar left_Color;
Scalar right_Color;

lanedetection::lanedetection(const Mat frame)
{
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
	blur(img_gray, img_edges, Size(3, 3));

	// Edge detection using canny detector
	minCannyThreshold = 47;
	maxCannyThreshold = 3 * minCannyThreshold;
	Canny(img_edges, img_edges, minCannyThreshold, maxCannyThreshold, 3, true);
	
	// Morphological Operation
	k = getStructuringElement(CV_SHAPE_RECT, Size(3, 3)); // morph_close (9, 9)
	morphologyEx(img_edges, img_edges, MORPH_DILATE, k);

	// Hough Transform
	rho				= 2;			// 4 war eingestellt
	theta			= CV_PI/180;
	threshold_hough	= 30;			// 200 war eingestellt threshold = 500/400, ist zu viel, reagiert nicht mehr! 120   45
	minLinLength	= 80;			// 110 war eingestellt
	maxLineGap		= 60;			// 20, 60, 150 war eingestellt
	
	counter_left = 0;
	counter_right = 0;
	
	HoughLinesP(img_edges, lines, rho, theta, threshold_hough, minLinLength, maxLineGap);
	
	// Draw Lines
	for(int i = 0; i < lines.size(); i++) {			
		Vec4i l = lines[i];  // p1 = x1, y1  p2 = x2, y2
		// Berechnung der Steigung aus dem Punkt mit m = ((y2 - y1) / (x2 -x1))
		// static_cast<double> wird verwendet, da ab c++ 11 integer-Division die Nachkommastellen weghaut.
		steigung = (static_cast<double>(l[3] - l[1]) / static_cast<double>(l[2] - l[0]));
		
		// Vergleich der Steigung kleiner/groeßer 0? und addieren diese auf einen neuen Vektor um anschließend Durchschnitt zu bilden.
		if(steigung < 0){
			counter_left++;
			left = left + l;
		}
		if(steigung > 0 ){
			counter_right++;
			right = right + l;
		}
	}
	// Durchschnitt der Vektoren left und right errechnen
	right = right / counter_right;
	left = left / counter_left;
	
	// Zeichen der Linien mit den Durchschnittswerten
	left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
	right_Color = Scalar(0,0,250);  // B=0 G=0 R=250
	line(frame_roi, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3, CV_NORMAL); // CV_AA vorher			
	line(frame_roi, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3, CV_NORMAL); // CV_AA vorher					
}
		
lanedetection::~lanedetection() {}

lanedetection::getEdgeImage()
{
    return img_edges;
}

lanedetection::getLaneImage()
{
	return frame;
}

lanedetection::getLeft()
{
	return left;
}

lanedetection::getRight()
{
	return right;
}
