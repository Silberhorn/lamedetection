#include <stdlib.h>

#include "lanecalculation.h"

using namespace std;
using namespace cv;

lanecalculation::lanecalculation(Vec4i left, Vec4i right)
{
	this->left = left;
	this->right = right;

    // Steigung links berechnen
	steigung_left = (static_cast<double>(left[3] - left[1]) / static_cast<double>(left[2] - left[0]));
	// Steigung rechts berechnen
	steigung_right = (static_cast<double>(right[3] - right[1]) / static_cast<double>(right[2] - right[0]));
	
	// Schnittpunkt der Fahrbahnbegrenzung mit der y-Achse
	y_achsenabschnitt_left = left[1] - steigung_left * left[0];
	y_achsenabschnitt_right = right[3] - steigung_right * right[2];
	
	// Schnittpunkt mit der x-Achse auf Höhe des Fahrzeugs (y = 480)
	x_Schnitt_left = (480.0 - y_achsenabschnitt_left) / steigung_left; 
	x_Schnitt_right = (480.0 - y_achsenabschnitt_right) / steigung_right; 
	
	// Berechnung Abstand zu Fahrbahnrand
	// ANNAHME:
	//	Breite SmartVideoCar:	~180mm
	//	Breite der Strecke:		~590mm
	// Distanz in Zentimeter (Faktor 0,034)
	distance_L = (0 - x_Schnitt_left) * 0.034;		
	distance_R = (x_Schnitt_right - 640) * 0.034;
}

lanecalculation::~lanecalculation() {}

string lanecalculation::getStringDistance()
{
	return "Distance left lane:  " + distance_L + " cm\n" + "Distance right lane: " + distance_R + " cm";
}
