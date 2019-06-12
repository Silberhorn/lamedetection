#ifndef BIRDSEYEVIEW_H_
#define BIRDSEYEVIEW_H_

using namespace std;
using namespace cv;

class birdseyeview
{
private:
	Mat imgSource;
	int alpha_;
	int focalLength;
	int dist;

	double alpha;
	double beta;
	double gamma;

	double w;
	double h;

	Mat A1;
	Mat RX;
	Mat RY;
	Mat RZ;
	Mat R;
	Mat T;
	Mat K;
	Mat transformationMat;

	Mat birdImg;

public:
	birdseyeview(Mat, int, int, int);
    ~birdseyeview();

	Mat getBirdsEyeView();
};

#endif	// BIRDSEYEVIEW_H_
