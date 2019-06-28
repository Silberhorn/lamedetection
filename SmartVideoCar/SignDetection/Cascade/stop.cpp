#include <wiringPi.h>
#include<iostream>
#include<opencv/cv.h>
#include<opencv2/objdetect/objdetect.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<sys/time.h>
#include<unistd.h>


using namespace std;
using namespace cv;

struct timeval tp;

#define LED_ROT 1
#define LED_GELB 2
#define LED_GRUEN 0
#define PAUSE 500

int main(){

	wiringPiSetup();
        pinMode(LED_ROT, OUTPUT);
	wiringPiSetup();
	pinMode(LED_GELB, OUTPUT);
        wiringPiSetup();
        pinMode(LED_GRUEN, OUTPUT);

	CascadeClassifier Detection;
  	bool cl = Detection.load("data/cascade.xml");

	if (!cl){
    		cout << "\n File is not loaded properly" << '\n';
    		exit(0);
  	}

	CascadeClassifier Detection2;
        bool cl2 = Detection2.load("data/stopSignDetector_yellow.xml");

        if (!cl2){
                cout << "\n File is not loaded properly" << '\n';
                exit(0);
        }


        CascadeClassifier Detection3;
        bool cl3 = Detection3.load("data/stopSignDetector_yellow.xml");

        if (!cl3){
                cout << "\n File is not loaded properly" << '\n';
                exit(0);
        }




	VideoCapture capture(0);
        capture.set(CV_CAP_PROP_FRAME_WIDTH,640);   // width in pixels  	380	480
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,360);   // height in pixels  	100	200

	if(!capture.isOpened()){   // connect to the camera
                cout << "Failed to connect to the camera." << endl;
        }

	Mat img_org;
	Rect region_of_interest = Rect(260,60,380,100);

	while(true){

		gettimeofday(&tp, NULL);
		long int ms1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    		capture >> img_org;          // capture the image to the frame
    		if(img_org.empty()){         // did the capture succeed?
	       		cout << "Failed to capture an image" << endl;
       			exit(0);
		}else{
			Mat img = img_org(region_of_interest);
			vector<Rect> signs;
    			Detection.detectMultiScale(img, signs, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

			vector<Rect> signs2;
                        Detection2.detectMultiScale(img, signs2, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

//                        vector<Rect> signs3;
//                        Detection3.detectMultiScale(img, signs3, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));  //detect

			if(signs.size() != 0){
				digitalWrite(LED_ROT, HIGH);
				//MOTOR AUS

			} else {
				digitalWrite(LED_ROT, LOW);
			}


    			for(int i = 0; i < signs.size(); i++){
      				Point pt1(signs[i].x, signs[i].y);
      				Point pt2((signs[i].x + signs[i].height), (signs[i].y + signs[i].width));
      				rectangle(img, pt1, pt2, Scalar(255, 255, 255), 2, 8, 0);
   			}
                        if(signs2.size() != 0){
                                digitalWrite(LED_GELB, HIGH);
                                //MOTOR AUS

                        } else {
                                digitalWrite(LED_GELB, LOW);
                        }


                        for(int i = 0; i < signs2.size(); i++){
                                Point pt12(signs2[i].x, signs2[i].y);
                                Point pt22((signs2[i].x + signs2[i].height), (signs2[i].y + signs2[i].width));
                                rectangle(img, pt12, pt22, Scalar(255, 255, 255), 2, 8, 0);
                        }

/**                        if(signs3.size() != 0){
                                digitalWrite(LED_GELB, HIGH);
                                //MOTOR AUS

                        } else {
                                digitalWrite(LED_GELB, LOW);
                        }


                        for(int i = 0; i < signs3.size(); i++){
                                Point pt13(signs3[i].x, signs3[i].y);
                                Point pt23((signs3[i].x + signs3[i].height), (signs3[i].y + signs3[i].width));
                                rectangle(img, pt13, pt23, Scalar(255, 255, 255), 2, 8, 0);
                        }
**/



			imshow( "Detecting Stop Signs", img);
			waitKey(1);

 		}
		gettimeofday(&tp, NULL);
		long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

		long int mss = ms2 - ms1;
		cout  << "0," << mss << "ms" << endl;

//		usleep(30);
	}
  	return 0;
}
