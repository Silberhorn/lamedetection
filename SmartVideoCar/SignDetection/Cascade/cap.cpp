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

using namespace cv;



int main(){

        VideoCapture capture(0);
        capture.set(CV_CAP_PROP_FRAME_WIDTH,640);   // width in pixels          380     480
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);   // height in pixels        100     200

	Mat img_org;

	for(int i = 0; i< 150; i++){

        	capture >> img_org;
		imshow( "Bilder", img_org);
                waitKey(50);
		String filename = "/media/pi/VOLUME/Bilder/Image" + i;
		imwrite(filename + ".jpg", img_org);
		//imwrite(os.path.join( "/boot/bilder/", "Image%d.jpg" %i), img_org);
	}
	return 0;
}
