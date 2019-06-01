#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "lanedetection.h"
#include "lanecalculation.h"

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

// Image Dimensions
const int IMAGEWIDTH 	= 640;
const int IMAGEHEIGHT	= 480;

Mat frame;

int main()
{
	VideoCapture cap(0);
	// Ab OpenCv3 ohne CV_ !
	cap.set(CV_CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout << "open error\n" << endl;
	        return -1;
	}

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
		
		// Window to show Original Image
		namedWindow("OrgImage");
		moveWindow("OrgImage", 10, 30);
		imshow("OrgImage", frameLines);
		
		// Window to show Edge Detection
		namedWindow("EdgeImage");
		moveWindow("EdgeImage", 10, 550);
		imshow("EdgeImage", frameEdges);
		
		// 50 = 50 ms | 27 = ESC zum abbrechen des Programms
		if(waitKey(50) == 27) {
			cout << "finished successful\n";
			break;
		}
	}
	
	return 0;
}
