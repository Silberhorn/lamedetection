#include <iostream>
//#include <stdlib.h>
//#include <unistd.h>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "signdetection.h"
#include "lanedetection.h"
#include "lanecalculation.h"
#include "rs232.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

// Image Dimensions
extern const int IMAGEWIDTH 	= 640;
extern const int IMAGEHEIGHT	= 360;

// Mittel der Fahrbahnspuren
extern Vec4i right_lane_avg		= {0};
extern Vec4i left_lane_avg		= {0};
extern int counter_left 		= 0;
extern int counter_right 		= 0;
extern CascadeClassifier Detection; 
extern CascadeClassifier Detection2;
extern bool cl;
extern bool cl2;
 

Mat frame;

// Serial Connection
const int CPORT_NR = 24;				// /dev/ttyACM0
const int BAUDRATE = 19200;				// 9600 baud
const char MODE[] = {'8', 'N', '1', 0};	// 8 data bits, no parity, 1 stop bit
// Stopschild		(value: 200)
// Vorfahrtsschild	(value: 210)
// steeringAngle	(value: 0 - 180)


static bool crossedLeftLaneFlag = false;
static bool crossedRightLaneFlag = false;

int main(int argc, char **argv)
{
	// Laden der Cascades fuer die Schilderkennung
	cl = Detection.load("./cascade.xml");
	if (!cl){
		cout << "\n Cascade (STOP SCHILD) is not loaded properly" << '\n';
		exit(0);
	}

	cl2 = Detection2.load("./stopSignDetector_yellow.xml");
	if (!cl2){
		cout << "\n Cascade (VORFAHRT GEWAEHREN) is not loaded properly" << '\n';
		exit(0);
	}

	VideoCapture cap(0);
	cap.set(CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout << "open error\n" << endl;
	        return -1;
	}

	// Com-Port verfügbar?
	if(RS232_OpenComport(CPORT_NR, BAUDRATE, MODE))
	{
		cout << "Can not open comport" << endl;
		return -1;
	}
	usleep(2000000);	// waits 2000ms for stable condition

	int8_t start = 210;	// Send START to Arduino
	RS232_SendByte(CPORT_NR, start); // sends byte on serial

	usleep(500000);

	// Window to show Original Image
	//namedWindow("LinesImage");
	//moveWindow("LinesImage", 10, 10);

	// Window to show Birds Eye View
	//namedWindow("BirdsImage");
	//moveWindow("BirdsImage", 10, 110);

	while(1) {
		auto start = chrono::steady_clock::now();

		//auto start_capture_frame = chrono::steady_clock::now();
		cap >> frame;
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}
		//auto end_capture_frame = chrono::steady_clock::now();

		lanedetection laneDetect(frame);
		signdetection signDetect(frame);

		Mat frameLines = laneDetect.getLaneImage();
		//Mat frameEdges = laneDetect.getEdgeImage();

		Vec4i leftLaneDetect = laneDetect.getLeft();
		Vec4i rightLaneDetect = laneDetect.getRight();

		lanecalculation laneCalc(leftLaneDetect, rightLaneDetect);

		// Punkt für Position des Textes
		//Point textPosition (10, (frame.rows - 30));
		//string distanceString = laneCalc.getStringDistance();

		// Text einfügen
		//putText(frameLines, distanceString, textPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar::all(255), 1, 8);

		//int8_t arduinoMsg = laneDetect.getSteeringAngle();

/*
		int d_left = 0;
		int d_right = 0;
		d_left = laneCalc.getDistanceLeft();
		d_right = laneCalc.getDistanceRight();

		if(d_left > 50 || d_left < -50) d_left = 0;

		cout << "Left : " << d_left << "\t\tRight : " << d_right << endl;


		steer = steer + (d_right - d_left);
		if(steer < 10)	steer = 10;
		if(steer > 170)	steer = 170;


		crossedLeftLaneFlag = (d_left < 0) ? true : false;
		crossedRightLaneFlag = (d_right < 0) ? true : false;
		if(crossedLeftLaneFlag)			steer = steer + 20;
		if(crossedRightLaneFlag)		steer = 40;
		if(laneDetect.getNoLineLeft())	steer = steer - 20;
		if(laneDetect.getNoLineRight())	steer = steer + 20;
		if(steer < 10)					steer = 10;
		if(steer > 170)					steer = 170;
*/

		uint8_t arduinoMsg = signDetect.getMotorSignal();

		RS232_SendByte(CPORT_NR, arduinoMsg); // sends byte on serial

		//imshow("LinesImage", frameLines);
		//imshow("EdgeImage", frameEdges);


		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		//if(waitKey(1) == 27) {
		//	cout << "finished successful\n";
		//	break;
		//}

		auto end = chrono::steady_clock::now();
		//cout << "Capture_Frame : " << chrono::duration_cast<chrono::milliseconds>(end_capture_frame - start_capture_frame).count() << " ms\t\t";
		cout << "Complete Algorythm : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;

	}

	return 0;
}
