#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <opencv2/opencv.hpp>   // C++ OpenCV include file


using namespace std;
using namespace cv;            // using the cv namespace too

int main()
{
    VideoCapture capture(0);   // capturing from /dev/video0
    // set any  properties in the VideoCapture object
    capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);   // width in pixels
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);   // height in pixels

    if(!capture.isOpened()){   // connect to the camera
       cout << "Failed to connect to the camera." << endl;
    }
    Mat frame, blured, gray, edges;    // original, grayscale and edge image
    Rect region_of_interest = Rect(0, 570, 1280, 100);

    namedWindow("lanedetect_edges", WINDOW_AUTOSIZE);// Create a window for display.

 //   while(1) {
        capture >> frame;          // capture the image to the frame
        if(frame.empty()){         // did the capture succeed?
           cout << "Failed to capture an image" << endl;
           return -1;
        }

	Mat frame_roi = frame(region_of_interest);

        GaussianBlur(frame_roi, blured, Size(3, 3), 0, 0, BORDER_DEFAULT);	// Aplly Gaussian Blur to reduce noise
        cvtColor(blured, gray, CV_BGR2GRAY);     // convert to grayscale
        Sobel(gray, edges, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);

        namedWindow("lanedetect_edges", WINDOW_AUTOSIZE);// Create a window for display.
        imshow("lanedetect_edges", edges);                   // Show our image inside it.
        waitKey(0);
//    }
    return 0;
}

