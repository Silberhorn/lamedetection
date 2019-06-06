#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "lanedetection.h"
#include "lanecalculation.h"
#include "rs232.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

// Image Dimensions
const int IMAGEWIDTH 	= 640;
const int IMAGEHEIGHT	= 480;

Mat frame;

// Serial Connection
const int CPORT_NR = 24;	/* /dev/ttyACM0 */
const int BAUDRATE = 57600;	/* 9600 baud */
const char MODE[] = {'8', 'N', '1', 0}; // 8 data bits, no parity, 1 stop bit
// Stopschild		(value: 200)
// Vorfahrtsschild	(value: 210)
// steeringAngle	(value: 0 - 180)

static bool crossedLeftLane = false;
static bool crossedRightLane = false;

int main()
{
	VideoCapture cap(0);
	// Ab OpenCv3 ohne CV_ !
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
	usleep(2000000);  /* waits 2000ms for stable condition */

	int8_t start = 210;
	RS232_SendByte(CPORT_NR, start); // sends byte on serial

	usleep(1000000);

	// Window to show Original Image
	//namedWindow("OrgImage");
	//moveWindow("OrgImage", 10, 30);

	// Window to show Edge Detection
	//namedWindow("EdgeImage");
	//moveWindow("EdgeImage", 10, 550);

	while(1) {
		cap >> frame;
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}

		lanedetection laneDetect(frame);

		Vec4i leftLaneDetect = laneDetect.getLeft();
		Vec4i rightLaneDetect = laneDetect.getRight();

		lanecalculation laneCalc(leftLaneDetect, rightLaneDetect);

		// Punkt für Position des Textes
		Point textPosition (10, (frame.rows - 30));
		Mat frameLines = laneDetect.getLaneImage();
		Mat frameEdges = laneDetect.getEdgeImage();
		string distanceString = laneCalc.getStringDistance();

		// Text einfügen
		putText(frameLines, distanceString, textPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar::all(255), 1, 8);

		int8_t steer = laneDetect.getSteeringAngle();

		if(laneDetect.getNoLineLeft()) {
			steer = 10;
		}
		if(laneDetect.getNoLineRight()) {
			steer = 170;
		}

		if(laneCalc.getDistanceLeft() < 0) {
			crossedLeftLane = true;
			steer = 170;
		} else {
			crossedLeftLane = false;
		}
		if(laneCalc.getDistanceRight() < 0) {
			crossedRightLane = true;
			steer = 10;
		} else {
			crossedRightLane = false;
		}

		RS232_SendByte(CPORT_NR, steer); // sends byte on serial

		//Vec4i middle = laneDetect.getMiddle();
		//cout << "Middle Points: " << middle << endl;

		/*
		double steigungLinks = laneDetect.getSteigungLeft();
		cout << "SteigLi: " << steigungLinks << "\t";
		double steigungRechts = laneDetect.getSteigungRight();
		cout << "SteigRe: " << steigungRechts << "\t";
		double steigungMiddle = laneDetect.getSteigungMiddle();
		cout << "SteigMi: " << steigungMiddle << "\n" << endl;
		*/


		//imshow("OrgImage", frameLines);
		//imshow("EdgeImage", frameEdges);


		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		//if(waitKey(50) == 27) {
		//	cout << "finished successful\n";
		//	break;
		//}
	}

	// Window to show Original Image
//	namedWindow("OrgImage");
//	moveWindow("OrgImage", 10, 30);
//	imshow("OrgImage", frameLines);

	// Window to show Edge Detection
//	namedWindow("EdgeImage");
//	moveWindow("EdgeImage", 10, 550);
//	imshow("EdgeImage", frameEdges);

	return 0;
}
