/********************************************************************************************************************/
/*	HAW Landshut																									*/
/*	Studienprojekt 2018/19																							*/
/*	SmartVideoCar																									*/
/*	Betreuer: Prof. Dr.-Ing. Martin Pellkofer																		*/
/*	Teilnehmer: Erkan Ertuerk, Tim Silberhorn, Lukas Spiel, Christoph Walther										*/
/*	Abgabe: 26.09.2019																								*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*											START: Include Libraries and Namespaces									*/
/********************************************************************************************************************/

// CPP Includes
#include <iostream>
#include <chrono>
#include <thread>

// OpenCV Includes
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

// Serial Connection Includes
#include "rs232.h"

// Namespaces
using namespace std;
using namespace cv;

/********************************************************************************************************************/
/*											END: Include Libraries and Namespaces									*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*											START: Global Variables Declaration										*/
/********************************************************************************************************************/

static const int IMAGEWIDTH 	= 320;
static const int IMAGEHEIGHT	= 180;

VideoCapture cap(0);						// Camera Modul

Mat videoFrame;								// Original captured frame from camera
Mat frameLanes;								// Cloned from videoFrame to detect lanes
Mat frameSigns;								// Cloned from videoFrame to detect signs
Mat frameFinal;								// Final frame, where both Signs and Lanes are merged

// Variables for SignDetection
CascadeClassifier Detection1;				// Cascade Classifier for Stop Sign Detection
CascadeClassifier Detection2;				// Cascade Classifier for Right Of Way Sign (startSign) Detection
int stopSignCounter;						// Counts how often a stopSign has been detected in a row
int startSignCounter;						// Counts how often a startSign has been detected in a row

// Variables for Steering Controller
int steeringValueAvg	= 90;				// Value for servomotor that is connected to the Arduino
int steeringValueNow	= 90;				// Current Steering Value for Steering Controller
int steeringValueLast	= 90;				// Last Steering Value for Steering Controller

// Serial Connection Settings
const int CPORT_NR	= 0;					// 24 := /dev/ttyACM0 (USB-connection), 0 := /dev/ttyS0 (GPIO-connection)
const int BAUDRATE	= 57600;				// standard = 9600
const char MODE[]	= {'8', 'N', '1', 0};	// 8 data bits, no parity, 1 stop bit
int arduinoMsg		= 90;					// Message that will be sent to the Arduino over this Serial Connection
// steeringAngle	(value: 0 - 180)
// Stopschild		(value: 200)
// Vorfahrtsschild	(value: 210)

/********************************************************************************************************************/
/*												END: Global Variables Declaration									*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*												START: Region of Interest Init										*/
/********************************************************************************************************************/

	// Region of Interest for Lanes
	int roi_x_L = 1;
	int roi_y_L = (IMAGEHEIGHT / 1.7);
	int roi_width_L = (IMAGEWIDTH - 1);
	int roi_height_L = (IMAGEHEIGHT - 10) - roi_y_L;
	Rect regionOfInterest_Lanes = Rect(roi_x_L, roi_y_L, roi_width_L, roi_height_L);

	// Region of Interest for Signs
	int roi_x_S = (int)(IMAGEWIDTH / 2.46);
	int roi_y_S = (int)(IMAGEHEIGHT / 12);
	int roi_width_S = (int)(IMAGEWIDTH / 1.685);
	int roi_height_S = (int)(IMAGEHEIGHT / 2.8);
	Rect regionOfInterest_Signs = Rect(roi_x_S, roi_y_S, roi_width_S, roi_height_S);

/********************************************************************************************************************/
/*												END: Region of Interest Init										*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*												START: Lanedetection Function										*/
/********************************************************************************************************************/

void laneDetectionAlgo(const Mat &frame, int &meanPosition, int &centerOffset)
{
	Mat frameROILanes;
	Mat grayFrame;
	Mat edgesFrame;
	Mat binaryFrame;

	// Variables for Sobel
	int scale	= 1; // optional scale factor for the computed derivative values; by default, no scaling is applied
	int delta	= 0; // optional delta value that is added to the results prior to storing them in edgeFrame
	// FROM OPENCV3 DOCUMENTATION:
	//	output datatype is cv2.CV_8U or np.uint8. But there is a slight problem with that.
	//	Black-to-White transition is taken as Positive slope (it has a positive value) while White-to-Black
	//	transition is taken as a Negative slope (It has negative value). So when you convert data to np.uint8,
	//	all negative slopes are made zero. In simple words, you miss that edge.
	int ddepth	= CV_8U;

	int counter = 0; // counts detected pixels after Sobel and inRange, to detect an "empty" image!

	// Convert to grayscale
	cvtColor(frame, grayFrame, CV_BGR2GRAY);
	// Run Sobel with (Input, Output, ddepth, xOrder, yOrder, ksize, scale, delta, borderType)
	Sobel(grayFrame, edgesFrame, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	// Convert from CV16S to CV8U
	//convertScaleAbs(edgesFrame, edgesFrame);
	// Create binaryFrame out of edgesFrame after Sobel
	inRange(edgesFrame, Scalar(80), Scalar(255), binaryFrame);
	// Create Region Of Interest For Binary Image
	frameROILanes = binaryFrame(regionOfInterest_Lanes);

	// Check every pixel in the image array for its value (true 1, false 0)
	for(int y = 0; y < frameROILanes.size().height; y++) {
		for(int x = 0; x < frameROILanes.size().width; x++) {
			int value = frameROILanes.at<int>(Point2f(x,y));
			if(value > 0) {
				meanPosition = meanPosition + x;
				counter++;
			}
		}
	}
	// if: Average Position of all detected (or white) pixels
	// else: give warning and set values to default
	if (counter != 0) {
		meanPosition = meanPosition / counter;
		// -1 to invert the Offset for Steering
		// -150 to shift the center Position of the Image
		centerOffset = -1 * (meanPosition - 150);
	}
	else {
		cout << "\tWARNING: Counter for MeanPosition Calculation is ZERO!" << endl;
		meanPosition = -1;
		centerOffset = 0;
	}
}

/********************************************************************************************************************/
/*												END: Lanedetection Function											*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*												START: Signdetection Function										*/
/********************************************************************************************************************/

void signDetectionAlgo(const Mat &frame, bool &startSignFlag, bool &stopSignFlag)
{
	Mat frameROISigns;

	vector<Rect> signs1;
	vector<Rect> signs2;

	frameROISigns = frame(regionOfInterest_Signs);

	Detection1.detectMultiScale(frameROISigns, signs1, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
	Detection2.detectMultiScale(frameROISigns, signs2, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));

	if(signs1.size() != 0)
	{
		//ARDUINO STOP
		stopSignCounter += 1;
		if(stopSignCounter >= 3)	stopSignFlag = true;

		// Rechteck um Schild zeichnen
		for(int i = 0; i < signs1.size(); i++)
		{
			Point pt1(signs1[i].x, signs1[i].y);
			Point pt2((signs1[i].x + signs1[i].height), (signs1[i].y + signs1[i].width));
			rectangle(frameROISigns, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	else {
		stopSignFlag = false;
		stopSignCounter = 0;
	}

	if(signs2.size() != 0)
	{
		//ARDUINO START
		startSignCounter += 1;
		if(startSignCounter >= 3)	startSignFlag = true;

		// Rechteck um Schild zeichnen
		for(int i = 0; i < signs2.size(); i++)
		{
			Point pt12(signs2[i].x, signs2[i].y);
			Point pt22((signs2[i].x + signs2[i].height), (signs2[i].y + signs2[i].width));
			rectangle(frameROISigns, pt12, pt22, Scalar(0, 255, 0), 2, 8, 0);
		}
	}
	else
	{
		startSignFlag = false;
		startSignCounter = 0;
	}
}

/********************************************************************************************************************/
/*												END: Signdetection Function											*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*													START: Main Function											*/
/********************************************************************************************************************/

int main(int argc, char **argv)
{

/********************************************************************************************************************/
/*										START: Open, Init and Check Camera and Comport								*/
/********************************************************************************************************************/

	cap.set(CV_CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Open Camera
	if(!cap.isOpened()) {
		cerr << "Can not open Camera!\n" << endl;
	    return -1;
	}

	cap >> videoFrame;
	if(videoFrame.empty()) {
		cerr << "Failed to capture Image!" << endl;
		return -1;
	}

	usleep(5000000);							// waits 5000ms for stable condition
	// Open Comport
	if(RS232_OpenComport(CPORT_NR, BAUDRATE, MODE))
	{
		cerr << "Can not open comport" << endl;
		return -1;
	}
	usleep(1000000);							// waits 1000ms for stable condition
	RS232_SendByte(CPORT_NR, 222);				// sends byte over serial to start Arduino Loop
	usleep(1000000);							// waits 1000ms for stable condition
	RS232_SendByte(CPORT_NR, 90);				// sends byte over serial to center the steering
	usleep(1000000);							// waits 1000ms for stable condition

/********************************************************************************************************************/
/*										END: Open, Init and Check Camera and Comport								*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*										START: Load Classifiers for SignDetection									*/
/********************************************************************************************************************/

	bool cl1 = false;
	bool cl2 = false;

	cout << "Loading Classifiers..." << "\t\t...Stop Sign...";

	cl1 = Detection1.load("./cascade_data/cascade.xml");
	if (!cl1){
		cerr << "\n Cascade for StopSign is not loaded properly" << '\n';
		return -1;
	}

	cout << "\t\t...Right of Way Sign..." << endl;

	cl2 = Detection2.load("./cascade_data/stopSignDetector_yellow.xml");
	if (!cl2){
		cerr << "\n Cascade for RightOfWaySign is not loaded properly" << '\n';
		return -1;
	}

/********************************************************************************************************************/
/*											END: Load Classifiers for SignDetection									*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*											START: Open Windows for Video Debugging									*/
/********************************************************************************************************************/

//	namedWindow("Original");
//	namedWindow("Edges");
//	namedWindow("Binary");
//	namedWindow("LaneDetection");
//	namedWindow("SignDetection");
//	namedWindow("Final");

/********************************************************************************************************************/
/*											END: Open Windows for Video Debugging									*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*													START: Algorithm Loop											*/
/********************************************************************************************************************/

	while(1)
	{
		// Start of time measurement
		auto start = chrono::steady_clock::now();

/********************************************************************************************************************/
/*												START: Lanekeeping Algorithm										*/
/********************************************************************************************************************/

			int meanPosition = 0;	// Average position of all detected pixels
			int centerOffset = 0;	// Difference between center of image and meanPosition

			frameLanes = videoFrame.clone();	// Make a copy of original frame

			// Run Lane Detection Algorithm in a Thread to spread workload across multiple cores
			thread threadLanes(laneDetectionAlgo, ref(frameLanes), ref(meanPosition), ref(centerOffset));

/********************************************************************************************************************/
/*												END: Lanekeeping Algorithm											*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*												START: Signdetection Algorithm										*/
/********************************************************************************************************************/

			bool stopSignFlag = false;	// Flag for detected sign
			bool startSignFlag = false;	// Flag for detected sign

			frameSigns = videoFrame.clone();	// Make a copy of original image

			// Run Sign Detection Algorithm in a Thread to spread workload across multiple cores
			thread threadSigns(signDetectionAlgo, ref(frameSigns), ref(startSignFlag), ref(stopSignFlag));

/********************************************************************************************************************/
/*												END: Signdetection Algorithm										*/
/********************************************************************************************************************/

		// Join both Threads (Program waits for each Thread to be completed...)
        threadLanes.join();		// Evtl ohne Thread, weil nicht rechenaufwaendig und evtl. stabiler?
        threadSigns.join();

/********************************************************************************************************************/
/*										START: Control Calculations for Arduino Uno									*/
/********************************************************************************************************************/

		steeringValueNow = centerOffset * 1.40 + 92;
		steeringValueAvg = (steeringValueNow + steeringValueLast) / 2;
		steeringValueLast = steeringValueAvg;


		if(stopSignFlag) {
			arduinoMsg = 200;
		}
		else if(startSignFlag) {
			arduinoMsg = 210;
		}
		else {
			arduinoMsg = steeringValueAvg;
		}

		// Send byte over serial connection to Arduino Uno
		RS232_SendByte(CPORT_NR, arduinoMsg);

/********************************************************************************************************************/
/*										END: Control Calculations for Arduino Uno									*/
/********************************************************************************************************************/

/********************************************************************************************************************/
/*												START: Debug Video for Desktop										*/
/********************************************************************************************************************/
/*
		// Draw ROI-Area for LaneDetection
		line(frameLanes, Point2f(roi_x_L, roi_y_L), Point2f(roi_x_L + roi_width_L, roi_y_L), Scalar(0,0,255), 1);
		line(frameLanes, Point2f(roi_x_L + roi_width_L, roi_y_L), Point2f(roi_x_L + roi_width_L, roi_y_L + roi_height_L), Scalar(0,0,255), 1);
		line(frameLanes, Point2f(roi_x_L + roi_width_L, roi_y_L + roi_height_L), Point2f(roi_x_L, roi_y_L + roi_height_L), Scalar(0,0,255), 1);
		line(frameLanes, Point2f(roi_x_L, roi_y_L + roi_height_L), Point2f(roi_x_L, roi_y_L), Scalar(0,0,255), 1);

		// Draw ROI-Area for SignDetection
		line(frameSigns, Point2f(roi_x_S, roi_y_S), Point2f(roi_x_S + roi_width_S, roi_y_S), Scalar(0,255,255), 1);
		line(frameSigns, Point2f(roi_x_S + roi_width_S, roi_y_S), Point2f(roi_x_S + roi_width_S, roi_y_S + roi_height_S), Scalar(0,255,255), 1);
		line(frameSigns, Point2f(roi_x_S + roi_width_S, roi_y_S + roi_height_S), Point2f(roi_x_S, roi_y_S + roi_height_S), Scalar(0,255,255), 1);
		line(frameSigns, Point2f(roi_x_S, roi_y_S + roi_height_S), Point2f(roi_x_S, roi_y_S), Scalar(0,255,255), 1);

		// Draw Steering Offset
		line(frameLanes, Point2f(158, IMAGEHEIGHT/1.4), Point2f(meanPosition, IMAGEHEIGHT/1.4), Scalar(0,0,255), 2);
		line(frameLanes, Point2f(158, IMAGEHEIGHT/1.5), Point2f(158, IMAGEHEIGHT/1.3), Scalar(0,0,255), 2);
		circle(frameLanes, Point2f(meanPosition, IMAGEHEIGHT/1.4), 6, Scalar(0,0,255), CV_FILLED);

		// Combine Lanes and Signs Image
		addWeighted(frameLanes, 0.5, frameSigns, 0.5, 0, frameFinal);

		// Show Images
//		imshow("Original", videoFrame);
//		imshow("Edges", edgesFrame);
//		imshow("Binary", binaryFrame);
//		imshow("LaneDetection", frameLanes);
//		imshow("SignDetection", frameSigns);
		imshow("FinalImage", frameFinal);

		// waitKey(x) x = ms | 27 = [ESC] to exit the Program
		if(waitKey(1) == 27) break;
*/
/********************************************************************************************************************/
/*												END: Debug Video for Desktop										*/
/********************************************************************************************************************/

		// End of time measurement
		auto end = chrono::steady_clock::now();

/********************************************************************************************************************/
/*											START: Debug Messages for Console										*/
/********************************************************************************************************************/

		cout << "[Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms]\t"
			<< "[START: " << (startSignFlag ? "X" : "_") << "  "
			<< "STOP: " << (stopSignFlag ? "X" : "_") << "]\t"
			<< "[MeanPos: " << meanPosition << "]\t"
			<< "[CenterOffset: " << centerOffset << "]\t"
			<< "[ArduinoMsg: " << (int)arduinoMsg << "]"
			<< endl;

/********************************************************************************************************************/
/*												END: Debug Messages for Console										*/
/********************************************************************************************************************/

		cap >> videoFrame;
		if(videoFrame.empty()) break;
	}

/********************************************************************************************************************/
/*													END: Algorithm Loop												*/
/********************************************************************************************************************/

	return 0;
}

/********************************************************************************************************************/
/*													END: Main Function												*/
/********************************************************************************************************************/

