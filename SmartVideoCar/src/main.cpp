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
#include "birdseyeview.h"
//#include "rs232.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

// Image Dimensions
const int IMAGEWIDTH 	= 640;
const int IMAGEHEIGHT	= 480;

Mat frame, frameBirdsEye, frameBirdsEyeEdges;
VideoCapture laneVideo;
Size videoSize; // Input Variable Size.

/*
// Serial Connection
const int CPORT_NR = 24;				// /dev/ttyACM0
const int BAUDRATE = 57600;				// 9600 baud
const char MODE[] = {'8', 'N', '1', 0};	// 8 data bits, no parity, 1 stop bit
// Stopschild		(value: 200)
// Vorfahrtsschild	(value: 210)
// steeringAngle	(value: 0 - 180)
*/

static bool crossedLeftLaneFlag = false;
static bool crossedRightLaneFlag = false;

int main(int argc, char **argv)
{
/*    //Load the video.
	if(argc < 2)
	{
		cerr << "There is no input video." << endl;
		return -1;
	}

	laneVideo.open(argv[1]); //Load the video.
	if(!laneVideo.isOpened())
	{
		cerr << "Could not open the video." << endl;
		return -1;
	}
	videoSize = Size(640, 480);

	laneVideo.set(CAP_PROP_POS_FRAMES, 0);
*/


	VideoCapture cap(0);
	// Ab OpenCv3 ohne CV_ !
	cap.set(CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout << "open error\n" << endl;
	        return -1;
	}

/*
	// Com-Port verfügbar?
	if(RS232_OpenComport(CPORT_NR, BAUDRATE, MODE))
	{
		cout << "Can not open comport" << endl;
		return -1;
	}
	usleep(2000000);	// waits 2000ms for stable condition


	int8_t start = 210;
	RS232_SendByte(CPORT_NR, start); // sends byte on serial

	usleep(1000000);
*/

	// Window to show Original Image
	namedWindow("LinesImage");
	moveWindow("LinesImage", 10, 10);

	// Window to show Birds Eye View
	namedWindow("BirdsImage");
	moveWindow("BirdsImage", 10, 110);

	// Window to show Birds Eye View
	namedWindow("BirdsEdgesImage");
	moveWindow("BirdsEdgesImage", 10, 210);

	// Window to show Edge Detection
	namedWindow("EdgeImage");
	moveWindow("EdgeImage", 10, 310);

	while(1) {
		//laneVideo >> frame;
		cap >> frame;
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}

		birdseyeview birdsEye(frame, 12, 500, 500);
		frameBirdsEye = birdsEye.getBirdsEyeView();

		lanedetection laneDetect(frame);

		Mat frameLines = laneDetect.getLaneImage();
		Mat frameEdges = laneDetect.getEdgeImage();

		birdseyeview birdsEyeEdges(frameEdges, 12, 500, 450);
		frameBirdsEyeEdges = birdsEyeEdges.getBirdsEyeView();
		//line(frameBirdsEyeEdges, Point(10, 470), Point(630, 470), Scalar(0,0,255), 1);
		arrowedLine(frameBirdsEyeEdges, Point(10, 470), Point(630, 470), Scalar(0,0,255), 1, 8, 0, 0.1);
		line(frameBirdsEyeEdges, Point(325, 469), Point(325, 471), Scalar(0,0,255), 1);
		arrowedLine(frameBirdsEyeEdges, Point(10, 470), Point(10, 10), Scalar(0,0,255), 1, 8, 0, 0.1);

		Vec4i leftLaneDetect = laneDetect.getLeft();
		Vec4i rightLaneDetect = laneDetect.getRight();

		lanecalculation laneCalc(leftLaneDetect, rightLaneDetect);

		// Punkt für Position des Textes
		Point textPosition (10, (frame.rows - 30));
		string distanceString = laneCalc.getStringDistance();

		// Text einfügen
		putText(frameLines, distanceString, textPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar::all(255), 1, 8);

		int8_t steer = laneDetect.getSteeringAngle();

		if(laneDetect.getNoLineLeft()) {
			steer = -steer;
		}
		if(laneDetect.getNoLineRight()) {
			steer = -steer;
		}

		if(laneCalc.getDistanceLeft() < 0) {
			crossedLeftLaneFlag = true;
			steer = 170;
		} else {
			crossedLeftLaneFlag = false;
		}
		if(laneCalc.getDistanceRight() < 0) {
			crossedRightLaneFlag = true;
			steer = 10;
		} else {
			crossedRightLaneFlag = false;
		}

/*
		RS232_SendByte(CPORT_NR, steer); // sends byte on serial

		Vec4i middle = laneDetect.getMiddle();
		cout << "Middle Points: " << middle << endl;

		double steigungLinks = laneDetect.getSteigungLeft();
		cout << "SteigLi: " << steigungLinks << "\t";
		double steigungRechts = laneDetect.getSteigungRight();
		cout << "SteigRe: " << steigungRechts << "\t";
		double steigungMiddle = laneDetect.getSteigungMiddle();
		cout << "SteigMi: " << steigungMiddle << "\n" << endl;
*/


		imshow("LinesImage", frameLines);
		imshow("BirdsImage", frameBirdsEye);
		imshow("BirdsEdgesImage", frameBirdsEyeEdges);
		imshow("EdgeImage", frameEdges);


		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		if(waitKey(0) == 27) {
			cout << "finished successful\n";
			break;
		}
	}

	return 0;
}
