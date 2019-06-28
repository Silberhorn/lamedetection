#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
 	//Open the default video camera
	VideoCapture cap(0);

 	// if not success, exit program
	 if (!cap.isOpened())  {
 		cout << "Cannot open the video camera" << endl;
  		cin.get(); //wait for any key press
  		return -1;
 	}


//        cap.set(CV_CAP_PROP_FRAME_WIDTH,380);   // width in pixels          380     480
//        cap.set(CV_CAP_PROP_FRAME_HEIGHT,100);   // height in pixels        100     200



 	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
 	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

 	string window_original = "Fahrzeug Kamera";
 	namedWindow(window_original); //create a window called "Fahrzeug Kamera"

 	while (true){
 		Mat frame;
  		bool bSuccess = cap.read(frame); // read a new frame from video

		//Breaking the while loop if the frames cannot be captured
  		if (bSuccess == false) {
   			cout << "Video camera is disconnected" << endl;
   			cin.get(); //Wait for any key press
   			break;
  		}

		IplImage* imgGrayScale = cvCreateImage(cvGetSize(frame), 8, 1);
 		cvCvtColor(frame,imgGrayScale,CV_BGR2GRAY);

  		//show the frame in the created window
  		imshow(window_original, frame);
		//imshow(window_edit, frame);

  		//wait for for 10 ms until any key is pressed.
  		//If the 'Esc' key is pressed, break the while loop.
  		//If the any other key is pressed, continue the loop
  		//If any key is not pressed withing 10 ms, continue the loop
  		if (waitKey(10) == 27){
   			cout << "Esc key is pressed by user. Stoppig the video" << endl;
   			break;
  		}
 	}
 	return 0;
}
