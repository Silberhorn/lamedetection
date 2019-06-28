#ifndef SIGNDETECTION_H_
#define SIGNDETECTION_H_

using namespace std;
using namespace cv;

class signdetection
{
private:
	// Region Of Interest
	int roi_x;
	int roi_y;
	int roi_width;
	int roi_height;
	Rect region_of_interest;

	// Matrix For Various Images
	Mat frame;
	Mat img_roi;
	
	CascadeClassifier Detection1; 
	CascadeClassifier Detection2;
    
	bool cl1;
	bool cl2;

	vector<Rect> signs1;
	vector<Rect> signs2;

	bool stopSignFlag;
	bool startSignFlag;
	


public:
	signdetection(Mat);
	~signdetection();

	Mat getSignImage();
    uint8_t getMotorSignal();
};

#endif	// SIGNDETECTION_H_
