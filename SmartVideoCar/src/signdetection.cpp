#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <wiringPi.h>

#include "signdetection.h"

using namespace std;
using namespace cv;

extern const int IMAGEWIDTH;
extern const int IMAGEHEIGHT;
extern bool loadFlag;
extern int stopSignCounter;
extern int startSignCounter;

signdetection::signdetection(Mat frame)
{
	this->frame = frame;

	// Region of Interest
	roi_x = (IMAGEWIDTH / 2.46);
	roi_y = (IMAGEHEIGHT / 12);
	roi_width = (IMAGEWIDTH / 1.685);
	roi_height = (IMAGEHEIGHT / 2.8);
	region_of_interest = Rect(roi_x, roi_y, roi_width, roi_height);	// 640x360 (x=260, y=60, w=380, h=100)
	img_roi = frame(region_of_interest);

        // Laden der Cascades fuer die Schilderkennung
        cl1 = Detection1.load("../cascade_data/cascade.xml");
        if (!cl1){
            cout << "\n Cascade (STOP SCHILD) is not loaded properly" << '\n';
            exit(0);
        }
        cl2 = Detection2.load("../cascade_data/stopSignDetector_yellow.xml");
        if (!cl2){
            cout << "\n Cascade (VORFAHRT) is not loaded properly" << '\n';
            exit(0);
        }

    Detection1.detectMultiScale(img_roi, signs1, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect min neighbors 3 statt 2
    Detection2.detectMultiScale(img_roi, signs2, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

    if(signs1.size() != 0){
        //ARDUINO STOP
        stopSignCounter += 1;
        if(stopSignCounter > 3) {
            stopSignFlag = true;
	    cout << "Stop erkannt, stopSignFlag = true!\n";
	}

	// Rechteck um Schild zeichnen
	for(int i = 0; i < signs1.size(); i++){
		Point pt1(signs1[i].x, signs1[i].y);
		Point pt2((signs1[i].x + signs1[i].height), (signs1[i].y + signs1[i].width));
		rectangle(img_roi, pt1, pt2, Scalar(255, 255, 255), 2, 8, 0);
	}

    } else {
        stopSignFlag = false;
	stopSignCounter = 0;
    }
    
    
    if(signs2.size() != 0){
        //ARDUINO START
	startSignCounter += 1;
        if(startSignCounter >= 3) {
	    startSignFlag = true;
	    cout << "Vorfahrt erkannt, startSignFlag = true!\n";
        }	
	// Rechteck um Schild zeichnen
	for(int i = 0; i < signs2.size(); i++){
		Point pt12(signs2[i].x, signs2[i].y);
		Point pt22((signs2[i].x + signs2[i].height), (signs2[i].y + signs2[i].width));
		rectangle(img_roi, pt12, pt22, Scalar(255, 255, 255), 2, 8, 0);
	}	
    } else{
	startSignFlag = false;
	startSignCounter = 0;
    }
}

signdetection::~signdetection() {}

Mat signdetection::getSignImage() {
    return frame;
}

uint8_t signdetection::getMotorSignal() {

    if(stopSignFlag) {
        return 200;
    }
    else if(startSignFlag) {
        return 210;
    }
    else {
        return 90;
    }
}
