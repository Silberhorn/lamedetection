#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

static const int IMAGEWIDTH 	= 320;
static const int IMAGEHEIGHT	= 180;

int main()
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout<<"open error\n";
	        return -1;
	}
	// Matrix für Bilder
	Mat frame, grayImg, LinesImg;

	// Bildausschnitt
	int roi_x = 1;
	int roi_y = (IMAGEHEIGHT / 2.6);
	int roi_width = (IMAGEWIDTH - 2);
	int roi_height = (IMAGEHEIGHT / 1.28) - roi_y;
	Rect region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 1, 185, 638, 190

	while(1) {
		auto start = chrono::steady_clock::now();
		cap >> frame;
		
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}
		auto end = chrono::steady_clock::now();

		// Region of Interest
		Mat frame_roi = frame(region_of_interest);

		// convert to grayscale
		cvtColor(frame_roi, grayImg, CV_BGR2GRAY);
		blur(grayImg, LinesImg, Size(3, 3));

		// Edge detection using canny detector
		static int minCannyThreshold = 50;		// min 230, max 500 funzt ganz gut
		int const max_lowThreshold = 150; // 1500 mag a gar ned //230 zuletzt nicht schlecht!
		int maxCannyThreshold = 3 * minCannyThreshold;
		Canny(LinesImg, LinesImg, minCannyThreshold, maxCannyThreshold, 3, true);
		// Create a Trackbar for user to enter threshold
		createTrackbar("Min Threshold:", "edges", &minCannyThreshold, max_lowThreshold);
		
		// Morphological Operation
		Mat k = getStructuringElement(CV_SHAPE_RECT, Size(9, 9)); // falls dilate 5,5
		//morphologyEx(LinesImg, LinesImg, MORPH_DILATE, k);
		morphologyEx(LinesImg, LinesImg, MORPH_CLOSE, k);
		
		namedWindow("edges");
		moveWindow("edges", 50, 550);
		imshow("edges", LinesImg);

		// hough transform
		double rho = 2; //4 war eingestellt
		double theta = CV_PI/180;
		int threshold = 30; // 200 war eingestellt threshold = 500/400, ist zu viel, reagiert nicht mehr! 120   45
		double minLinLength = 110; //110 war eingestellt
		double maxLineGap = 60; //20, 60, 150 war eingestellt
		
		double steigung, steigung_left, y_achsenabschnitt_left, x_Schnitt_left;
		double steigung_right, y_achsenabschnitt_right, x_Schnitt_right;
		
		// Vektoren 
		vector<Vec4i> lines;
		vector<Vec4i> lines_left;
		vector<Vec4i> lines_right;
		Vec4i left;
		Vec4i right;
		
		HoughLinesP(LinesImg, lines, rho, theta, threshold, minLinLength, maxLineGap);

		for(int i = 0; i < lines.size(); i++) {
			Vec4i l = lines[i];  // p1=x1,y1  p2=x2,y2
			
			//Berechnung der Steigung aus dem Punkt mit m = ((y2 - y1) / (x2 -x1))
			//static_cast<double> wird verwendet, da ab c++ 11 integer-Division die Nachkommastellen weghaut.
			steigung = (static_cast<double>(l[3] - l[1]) / static_cast<double>(l[2] - l[0]));
			
			//Ausgabe der Steigung und Punktkoordinaten
			///cout << "steigung = " << steigung << endl;
			///cout << "l[0,1,2,3] = " << l << endl;
			
			// Vergleich der Steigung kleiner 0? groeßer 0? und addieren diese auf einen neuen Vektor um anschließend Durchschnitt zu bilden.
			if(steigung < 0.2){
				// NEUERT ANSATZ: IM BILD LINKS?
				if(l[0] < (IMAGEWIDTH / 2) && l[2] < (IMAGEWIDTH / 2)) {
					// LINKE FAHRSPUR
					lines_left.push_back(l);
				}
			}
			if(steigung > 0.2){
				// NEUERT ANSATZ: IM BILD RECHTS?
				if(l[0] > (IMAGEWIDTH / 2) && l[2] > (IMAGEWIDTH / 2)) {
					// RECHTE FAHRSPUR
					lines_right.push_back(l);
				}
			}
		}
		
		float lane_length_left = 0.0;
		float lane_length_right = 0.0;

		for(int i = 0; i < lines_left.size(); i++) {
			Vec4i l = lines_left[i];
			point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
			float d = boost::geometry::distance(p1, p2);
			if(lane_length_left < d) {
				lane_length_left = d;
				left = l;
			}
		}

		for(int i = 0; i < lines_right.size(); i++) {
			Vec4i l = lines_right[i];
			point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
			float d = boost::geometry::distance(p1, p2);
			if(lane_length_right < d) {
				lane_length_right = d;
				right = l;
			}
		}
		
		// steigung links
		steigung_left = (static_cast<double>(left[3] - left[1]) / static_cast<double>(left[2] - left[0]));
		// steigung rechts
		steigung_right= (static_cast<double>(right[3] - right[1]) / static_cast<double>(right[2] - right[0]));
		
		// y = b wenn x = 0!
		y_achsenabschnitt_left = left[1] - steigung_left * left[0];
		y_achsenabschnitt_right = right[3] - steigung_right * right[2];
		
		// Schnitt mit der x-Achse auf Höhe des Fahrzeugs (y=480)
		x_Schnitt_left = (180.0 - y_achsenabschnitt_left) / steigung_left; 
		x_Schnitt_right = (180.0 - y_achsenabschnitt_right) / steigung_right; 
		
		// Berechnung Abstand zu linker Linie
		// ANNAHME:
		//	Breite SmartVideoCar:	180mm ()
		//	Breite der Strecke:		590mm
		int distance_L = (0 - x_Schnitt_left) * 0.034;		// Distanz in Millimeter (Faktor 0,34)
		int distance_R = (x_Schnitt_right - 640) * 0.034;	// Distanz in Millimeter (Faktor 0,34)
		
		// Zeichen der Linien mit den Durchschnittswerten
		Scalar left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
		Scalar right_Color = Scalar(0,0,250);  // B=0 G=0 R=250
		line(frame_roi, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3, CV_NORMAL);
		line(frame_roi, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3, CV_NORMAL);

		string distance_Left = "Distance left lane:  " + to_string(distance_L) + " cm";
		string distance_Right= "Distance right lane: " + to_string(distance_R) + " cm";
		
		Point textPositionLeft (10, (frame.rows - 30));
		Point textPositionRight(10, (frame.rows - 10));
		putText(frame, distance_Left, textPositionLeft, FONT_HERSHEY_SIMPLEX, 0.5, Scalar::all(255), 1, 8);
		putText(frame, distance_Right,textPositionRight,FONT_HERSHEY_SIMPLEX, 0.5, Scalar::all(255), 1, 8);
		
		namedWindow("frame");
		moveWindow("frame", 50, 30);
		imshow("frame", frame);
		
		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		if(waitKey(50) == 27) {
			cout << "finish successful\n";
			break;
		}
		cout << "capture time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms " << endl;
	}
	return 0;
}
