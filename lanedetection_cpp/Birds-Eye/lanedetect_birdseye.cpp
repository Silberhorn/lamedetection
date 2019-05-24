#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

Mat frame, frame2, linesImg;

Mat birdsEyeView(Mat imgSource, int alpha_, int focalLength, int dist) {
		Mat birdImg;
		double alpha, beta, gamma; 

		alpha =((double)alpha_ -90) * CV_PI/180;
		beta = 0.0;
		gamma = 0.0;

		Size image_size = imgSource.size();
		double w = (double)image_size.width, h = (double)image_size.height;


		// Projection matrix 2D -> 3D
		Mat A1 = (Mat_<float>(4, 3)<< 
			1, 0, -w/2,
			0, 1, -h/2,
			0, 0, 0,
			0, 0, 1 );

	
		// Rotation matrices Rx, Ry, Rz

		Mat RX = (Mat_<float>(4, 4) << 
			1, 0, 0, 0,
			0, cos(alpha), -sin(alpha), 0,
			0, sin(alpha), cos(alpha), 0,
			0, 0, 0, 1 );

		Mat RY = (Mat_<float>(4, 4) << 
			cos(beta), 0, -sin(beta), 0,
			0, 1, 0, 0,
			sin(beta), 0, cos(beta), 0,
			0, 0, 0, 1	);

		Mat RZ = (Mat_<float>(4, 4) << 
			cos(gamma), -sin(gamma), 0, 0,
			sin(gamma), cos(gamma), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1	);


		// R - rotation matrix
		Mat R = RX * RY * RZ;

		// T - translation matrix
		Mat T = (Mat_<float>(4, 4) << 
			1, 0, 0, 0,  
			0, 1, 0, 0,  
			0, 0, 1, dist,  
			0, 0, 0, 1); 
		
		// K - intrinsic matrix 
		Mat K = (Mat_<float>(3, 4) << 
			focalLength, 0, w/2, 0,
			0, focalLength, h/2, 0,
			0, 0, 1, 0
			); 


		Mat transformationMat = K * (T * (R * A1));

		warpPerspective(imgSource, birdImg, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);

		return birdImg;
}

int main()
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout<<"open error\n";
	        return -1;
	}
	// Matrix für Bilder
	Mat grayImg;
	// Bildausschnitt 
	Rect region_of_interest = Rect(1, 200, 638, 190);
	
	// Open Windows for Image Display
	namedWindow("Bird's-Eye", 1);
	moveWindow("Bird's-Eye", 1300, 30);
	namedWindow("edges");
	moveWindow("edges", 650, 30);
	namedWindow("frame");
	moveWindow("frame", 0, 30);


	while(1) {
		cap >> frame;
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}
		
		frame = birdsEyeView(frame, 8, 790, 1038);
		
		imshow("Bird's-Eye", frame);
		
			
		
		

		// Region of Interest
		// Mat frame_roi = frame(region_of_interest);

		// convert to grayscale
		cvtColor(frame, grayImg, CV_BGR2GRAY);
		blur(grayImg, linesImg, Size(3, 3));

		// Edge detection using canny detector
		int minCannyThreshold;		// min 230, max 500 funzt ganz gut
		int const max_lowThreshold = 170; // 1500 mag a gar ned //230 zuletzt nicht schlecht!
		int maxCannyThreshold = 170;
		//Sobel(linesImg, linesImg, -1, 0, 1, 3, BORDER_DEFAULT);
		Canny(linesImg, linesImg, minCannyThreshold, maxCannyThreshold, 3, true);
	
		// Create a Trackbar for user to enter threshold
		createTrackbar("Min Threshold:", "edges", &minCannyThreshold, max_lowThreshold);

		// Morphological Operation
		Mat k = getStructuringElement(CV_SHAPE_RECT, Size(13, 13)); // falls dilate 5,5
		
		//kleiner Test
		// dilate(linesImg, linesImg, k);
		morphologyEx(linesImg, linesImg, MORPH_CLOSE, k);
		

		imshow("edges", linesImg);

		// hough transform
		double rho = 2; //4 war eingestellt
		double theta = CV_PI/180;
		int threshold = 45; // 200 war eingestellt threshold = 500/400, ist zu viel, reagiert nicht mehr! 120 
		double minLinLength = 110; //35 war eingestellt
		double maxLineGap = 60; //20 war eingestellt
		double steigung;
		
		// Vektoren 
		vector<Vec4i> lines;
		Vec4i left;
		Vec4i right;
		
		
		HoughLinesP(linesImg, lines, rho, theta, threshold, minLinLength, maxLineGap);

		//draw lines
		//cout << "lines.size = " << lines.size() << endl;
		int counter_left = 0;
		int counter_right = 0;
		
		for(int i = 0; i < lines.size(); i++) {			
			Vec4i l = lines[i];  // p1=x1,y1  p2=x2,y2
			//Berechnung der Steigung aus dem Punkt mit m = ((y2 - y1) / (x2 -x1))
			// static_cast<double> wird verwendet, da ab c++ 11 integer-Division die Nachkommastellen weghaut.
			steigung = (static_cast<double>(l[3] - l[1]) / static_cast<double>(l[2] - l[0]));
			//Ausgabe der Steigung und Punktkoordinaten
			//cout << "steigung = " << steigung << endl;
			//cout << "l[0,1,2,3] = " << l << endl;
			// Vergleich der Steigung kleiner 0? groeßer 0? und addieren diese auf einen neuen Vektor um anschließend Durchschnitt zu bilden.
			if(steigung < 0){
				counter_left++;
				left = left + l;
			}
			if(steigung > 0 ){
				counter_right++;
				right = right + l;
			}
		}
		// Durchschnitt der Vektoren left und right!
		right = right / counter_right;
		left = left / counter_left;
		
		//cout << "left = " << left << endl;
		//cout << "right = " << right << endl;
		
		// Zeichen der Linien mit den Durchschnittswerten
		Scalar left_Color = Scalar(0,250,0);  // B=0 G=250 R=0
		Scalar right_Color = Scalar(0,0,250);  // B=0 G=250 R=0
		line(frame, Point(left[0], left[1]), Point(left[2], left[3]), left_Color, 3, CV_NORMAL); // CV_AA vorher			
		line(frame, Point(right[0], right[1]), Point(right[2], right[3]), right_Color, 3, CV_NORMAL); // CV_AA vorher			
		
		
		// Berechnung Abstand zu linker Linie
		// ANNAHME:
		//	Breite SmartVideoCar:	180mm ()
		//	Breite der Strecke:		590mm
		point_xy<float> pCenter(319.0, left[1]), pLeft(left[0], left[1]);
		float distanceLeft = boost::geometry::distance(pCenter, pLeft);
		//cout << "Distance left lane: " << distanceLeft << endl;


		frame2 = birdsEyeView(frame, 90, 500, 500);

		string distance_Left = "Distance left lane: " + to_string(distanceLeft);
		
		Point textPosition(10, (frame2.rows - 10));
		putText(frame2, distance_Left, textPosition, FONT_HERSHEY_SIMPLEX, 1, Scalar::all(255), 2, 8);
		
		imshow("frame", frame2);
		
		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		if(waitKey(50) == 27) {
			cout << "finish successful\n";
			break;
		}
	}
	return 0;
}
