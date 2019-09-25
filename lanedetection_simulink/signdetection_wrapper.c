
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <objdetect/objdetect.hpp>
#include <imgproc/imgproc.hpp>
#include <core/core.hpp>
#include <opencv2/opencv.hpp>
#include <highgui/highgui.hpp>
#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
#include <opencv/cv.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 480
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void signdetection_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
using namespace std;
using namespace cv;

#define LEUCHTDIODE_ROT 1
#define LEUCHTDIODE_GELB 2

	wiringPiSetup();
    pinMode(LEUCHTDIODE_ROT, OUTPUT);
	wiringPiSetup();
	pinMode(LEUCHTDIODE_GELB, OUTPUT);
    
    Rect region_of_interest = Rect(260,140,380,100);
    
	CascadeClassifier Detection;
  	bool cl = Detection.load("data/cascade.xml");

	CascadeClassifier Detection2;
    bool cl2 = Detection2.load("data/stopSignDetector_yellow.xml");
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void signdetection_Outputs_wrapper(const uint8_T *image,
			boolean_T *stop)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
 */

Mat img = image(region_of_interest);
vector<Rect> signs;
Detection.detectMultiScale(img, signs, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

if(signs.size() != 0){
	digitalWrite(LEUCHTDIODE_ROT, HIGH);
	stop = true;
} else {
	digitalWrite(LEUCHTDIODE_ROT, LOW);
}

for(int i = 0; i < signs.size(); i++){
    Point pt1(signs[i].x, signs[i].y);
	Point pt2((signs[i].x + signs[i].height), (signs[i].y + signs[i].width));
	rectangle(img, pt1, pt2, Scalar(255, 255, 255), 2, 8, 0);
}

vector<Rect> signs2;
Detection2.detectMultiScale(img, signs2, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

if(signs2.size() != 0){
    digitalWrite(LEUCHTDIODE_GELB, HIGH);
} else {
    digitalWrite(LEUCHTDIODE_GELB, LOW);
}

for(int i = 0; i < signs2.size(); i++){
    Point pt12(signs2[i].x, signs2[i].y);
    Point pt22((signs2[i].x + signs2[i].height), (signs2[i].y + signs2[i].width));
    rectangle(img, pt12, pt22, Scalar(255, 255, 255), 2, 8, 0);
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


