#include "lanedetection.h"

lanedetection::lanedetection(const Mat frame):
{
	// Region of Interest
	roi_x = 1;
	roi_y = (IMAGEHEIGHT / 2.6);
	roi_width = (IMAGEWIDTH - 2);
	roi_height = (IMAGEHEIGHT / 1.28) - roi_y;
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 1, 185, 638, 190
	frame_roi = frame(region_of_interest);

	// Convert to Grayscale
	cvtColor(frame_roi, img_gray, CV_BGR2GRAY);
	// Blur image for less noise
	blur(img_gray, img_edges, Size(3, 3));

	// Edge detection using canny detector
	minCannyThreshold = 47;
	max_lowThreshold = 800;	// Max Value for Trackbar
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

	///cout << "lines.size = " << lines.size() << endl;
	
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
	
	// Steigung links berechnen
	steigung_left = (static_cast<double>(left[3] - left[1]) / static_cast<double>(left[2] - left[0]));
	// Steigung rechts berechnen
	steigung_right = (static_cast<double>(right[3] - right[1]) / static_cast<double>(right[2] - right[0]));
	
	// y = b wenn x = 0!
	y_achsenabschnitt_left = left[1] - steigung_left * left[0];
	y_achsenabschnitt_right = right[3] - steigung_right * right[2];
	
	// Schnitt mit der x-Achse auf Höhe des Fahrzeugs (y=480)
	x_Schnitt_left = (480.0 - y_achsenabschnitt_left) / steigung_left; 
	x_Schnitt_right = (480.0 - y_achsenabschnitt_right) / steigung_right; 
	
	// Berechnung Abstand zu Fahrbahnrand
	// ANNAHME:
	//	Breite SmartVideoCar:	~180mm
	//	Breite der Strecke:		~590mm
	// Distanz in Zentimeter (Faktor 0,034)
	distance_L = (0 - x_Schnitt_left) * 0.034;		
	distance_R = (x_Schnitt_right - 640) * 0.034;
	
	// Zeichen der Linien mit den Durchschnittswerten
	left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
	right_Color = Scalar(0,0,250);  // B=0 G=0 R=250
	line(frame_roi, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3, CV_NORMAL); // CV_AA vorher			
	line(frame_roi, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3, CV_NORMAL); // CV_AA vorher					
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

string lanedetection::getStringDistance()
{
	return "Distance left lane:  " + to_string(distance_L) + " cm\n" + "Distance right lane: " + to_string(distance_R) + " cm";
}
