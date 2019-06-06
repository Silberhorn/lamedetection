#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "lanecalculation.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

lanecalculation::lanecalculation(Vec4i left, Vec4i right)
{
	this->left = left;
	this->right = right;

	int IMAGEHEIGHT = 480;
	int IMAGEWIDTH = 640;

    // Steigung links berechnen
	steigung_left = (static_cast<double>(left[3] - left[1]) / static_cast<double>(left[2] - left[0]));
	// Steigung rechts berechnen
	steigung_right = (static_cast<double>(right[3] - right[1]) / static_cast<double>(right[2] - right[0]));

	// Schnittpunkt der Fahrbahnbegrenzung mit der y-Achse
	y_achsenabschnitt_left = left[1] - steigung_left * left[0];
	y_achsenabschnitt_right = right[3] - steigung_right * right[2];

	// Schnittpunkt mit der x-Achse auf Höhe des Fahrzeugs (y = 480)
	x_Schnitt_left = (static_cast<double>(IMAGEHEIGHT) - y_achsenabschnitt_left) / steigung_left;
	x_Schnitt_right = (static_cast<double>(IMAGEHEIGHT) - y_achsenabschnitt_right) / steigung_right;

	// Berechnung Abstand zu Fahrbahnrand
	// ANNAHME:
	//	Breite SmartVideoCar:	~180mm
	//	Breite der Strecke:		~590mm
	// Distanz in Zentimeter (Faktor 0,034)
	distance_L = (0 - x_Schnitt_left) * 0.034;
	distance_R = (x_Schnitt_right - IMAGEWIDTH) * 0.034;
}

lanecalculation::~lanecalculation() {}

int lanecalculation::getDistanceLeft()
{
	return distance_L;
}

int lanecalculation::getDistanceRight()
{
	return distance_R;
}

string lanecalculation::getStringDistance()
{
	return "Distance left lane:  " + to_string(distance_L) + " cm | " + "Distance right lane: " + to_string(distance_R) + " cm";
}
