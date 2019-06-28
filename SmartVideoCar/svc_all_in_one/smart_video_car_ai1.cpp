#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

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





void lanedetection(Mat frame)
{
	this->frame = frame;

	// Region of Interest
	roi_x = 1;
	roi_y = (IMAGEHEIGHT / 2);
	roi_width = (IMAGEWIDTH - 2);
	roi_height = (IMAGEHEIGHT / 1.25) - roi_y;
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 640x480 (x=1, y=185, w=638, h=190)
	frame_roi = frame(region_of_interest);

	// Convert to Grayscale
	cvtColor(frame_roi, img_gray, COLOR_BGR2GRAY);
	// Blur image for less noise
	blur(img_gray, img_edges, cv::Size(3, 3));

	// Edge detection using canny detector
	minCannyThreshold = 50;
	maxCannyThreshold = 3 * minCannyThreshold;
	Canny(img_edges, img_edges, minCannyThreshold, maxCannyThreshold, 3, true);

	// Morphological Operation
	k = getStructuringElement(MORPH_RECT, Size(9, 9)); // morph_close (9, 9)
	morphologyEx(img_edges, img_edges, MORPH_CLOSE, k);

	// Hough Transform
	rho				= 2;
	theta			= CV_PI / 180;
	threshold_hough	= 30;
	minLinLength	= 110;
	maxLineGap		= 60;

	HoughLinesP(img_edges, lines, rho, theta, threshold_hough, minLinLength, maxLineGap);


	float lane_length_left = 0.0;
	float lane_length_right = 0.0;

	// Differentiate Left and Right Lane
	for(int i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];  // p1=x1,y1  p2=x2,y2

		// Berechnung der Steigung aus dem Punkt mit m = ((y2 - y1) / (x2 -x1))
		steigung = (static_cast<double>(l[3] - l[1]) / static_cast<double>(l[2] - l[0]));

		// WENN Steigung kleiner 0.2, DANN moeglicherweise linke Fahrspurbegrenzung
		if(steigung < -0.2){
			// Liegen beide Punkte der Linie im linken Bildbereich?
			if(l[0] < (IMAGEWIDTH / 2) && l[2] < (IMAGEWIDTH / 2)) {
//				lines_left.push_back(l);
				point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
				float d = boost::geometry::distance(p1, p2);
				if(lane_length_left < d) {
					lane_length_left = d;
					left = l;
				}
			}
		}
		// WENN Steigung groesser 0.2, DANN moeglicherweise rechte Fahrspurbegrenzung
		if(steigung > 0.2){
			// Liegen beide Punkte der Linie im rechten Bildbereich?
			if(l[0] > (IMAGEWIDTH / 2) && l[2] > (IMAGEWIDTH / 2)) {
//				lines_right.push_back(l);
				point_xy<float> p1(l[0], l[1]), p2(l[2], l[3]);
				float d = boost::geometry::distance(p1, p2);
				if(lane_length_right < d) {
					lane_length_right = d;
					right = l;
				}
			}
		}
	}
	if(left[0] == 0 && left[1] == 0 && left[2] == 0 && left[3] == 0) {
		left[0] = right[2] / 2;
		left[1] = right[3];
		left[2] = right[0] / 2;
		left[3] = right[1];
		noLineLeft = true;
		left_Color = Scalar(255,0,0);  // B=0 G=250 R=0
	} else {
		noLineLeft = false;
	}
	if(right[0] == 0 && right[1] == 0 && right[2] == 0 && right[3] == 0) {
		right[0] = left[2] * 2;
		right[1] = left[3];
		right[2] = left[0] * 2;
		right[3] = left[1];
		noLineRight = true;
		right_Color = Scalar(255,0,0);  // B=0 G=0 R=250
	} else {
		noLineRight = false;
	}
	if(noLineLeft == false) {
		if(counter_left != 1) {
			left_lane_avg[0] = left[0];
			left_lane_avg[1] = left[1];
			left_lane_avg[2] = left[2];
			left_lane_avg[3] = left[3];
			counter_left = 1;
		} else {
			left_lane_avg[0] = (left_lane_avg[0] + left[0]) / 2;
			left_lane_avg[1] = (left_lane_avg[1] + left[1]) / 2;
			left_lane_avg[2] = (left_lane_avg[2] + left[2]) / 2;
			left_lane_avg[3] = (left_lane_avg[3] + left[3]) / 2;
		}
	}
	if(noLineRight == false) {
		if(counter_right != 1) {
			right_lane_avg[0] = right[0];
			right_lane_avg[1] = right[1];
			right_lane_avg[2] = right[2];
			right_lane_avg[3] = right[3];
			counter_right = 1;
		} else {
			right_lane_avg[0] = (right_lane_avg[0] + right[0]) / 2;
			right_lane_avg[1] = (right_lane_avg[1] + right[1]) / 2;
			right_lane_avg[2] = (right_lane_avg[2] + right[2]) / 2;
			right_lane_avg[3] = (right_lane_avg[3] + right[3]) / 2;
		}
	}
	middle[0] = (left_lane_avg[0] + right_lane_avg[2]) / 2;
	middle[1] = (left_lane_avg[1] + right_lane_avg[3]) / 2;
	middle[2] = (left_lane_avg[2] + right_lane_avg[0]) / 2;
	middle[3] = (left_lane_avg[3] + right_lane_avg[1]) / 2;
}


int getSteeringAngle()
{
	int middle_point_offset = 0;

	// Berechnung des Abstands zur Bildmitte (links von mitte negativ, rechts positiv)
	middle_point_offset = ((middle[0] + middle[2]) / 2) - 320;

	// Faktor und Offset
	middle_point_offset = middle_point_offset * 0.35 + 90;	// 0.28

	//cout << "Steering: " << middle_point_offset << endl;

	if(middle_point_offset < 20) {
		middle_point_offset = 20;
	}
	if(middle_point_offset > 160) {
		middle_point_offset = 160;
	}

	return middle_point_offset;
}


void signdetection(Mat img_org)
{
	this->img_org = img_org;

	// Region of Interest
	roi_x = (IMAGEWIDTH / 2.46);
	roi_y = (IMAGEHEIGHT / 6);
	roi_width = (IMAGEWIDTH / 1.685);
	roi_height = (IMAGEHEIGHT / 3.6);
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 640x360 (x=260, y=60, w=380, h=100)
    img = img_org(region_of_interest);

    // Laden der Cascades fuer die Schilderkennung
	cl1 = Detection1.load("./cascade.xml");
	if (!cl1){
		cout << "\n Cascade (STOP SCHILD) is not loaded properly" << '\n';
		exit(0);
	}

	cl2 = Detection2.load("./stopSignDetector_yellow.xml");
	if (!cl2){
		cout << "\n Cascade (VORFAHRT) is not loaded properly" << '\n';
		exit(0);
	}

    Detection1.detectMultiScale(img, signs1, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect min neighbors 3 statt 2
    Detection2.detectMultiScale(img, signs2, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

    if(signs1.size() != 0){
        //digitalWrite(LED_ROT, HIGH);
        //ARDUINO STOP
        if(stopSignCounter > 3) {
            stopSignFlag = true;
        }
        stopSignCounter += 1;
    } else {
        //digitalWrite(LED_ROT, LOW);
        stopSignFlag = false;
        stopSignCounter = 0;
    }

    if(signs2.size() != 0){
        //digitalWrite(LED_GELB, HIGH);
        //ARDUINO START
        if(startSignCounter > 3) {
            startSignFlag = true;
        }
        startSignCounter += 1;
    } else {
        //digitalWrite(LED_GELB, LOW);
        startSignFlag = false;
        startSignCounter = 0;
    }
}

void loadClassifier() {
    // Laden der Cascades fuer die Schilderkennung
	cl1 = Detection1.load("./cascade.xml");
	if (!cl1){
		cout << "\n Cascade (STOP SCHILD) is not loaded properly" << '\n';
		exit(0);
	}

	cl2 = Detection2.load("./stopSignDetector_yellow.xml");
	if (!cl2){
		cout << "\n Cascade (VORFAHRT) is not loaded properly" << '\n';
		exit(0);
	}
}

uint8_t getMotorSignal() {
    if(stopSignFlag) {
        return 200;
    }
    if(startSignFlag) {
        return 210;
    }
}





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
