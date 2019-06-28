#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

static const int IMAGEWIDTH 	= 640;
static const int IMAGEHEIGHT	= 480;



int main()
{
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, IMAGEWIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGEHEIGHT);

	// Kamera verfügbar?
	if(!cap.isOpened()) {
		cout<<"open error\n";
	        return -1;
	}
	
	Mat frame;

	while(1) {
		auto start = chrono::steady_clock::now();
		cap >> frame;
		
		if(frame.empty()) {
			cout << "capture error\n" << endl;
		}
		auto end = chrono::steady_clock::now();

		cout << "capture time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms " << endl;
	}
	return 0;
}
