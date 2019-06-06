#ifndef LANEDETECTION_H_
#define LANEDETECTION_H_

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

class lanedetection
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
	Mat frame_roi;
	Mat img_gray;
	Mat img_edges;
	Mat img_lines;

	// Canny
	int minCannyThreshold;
	int maxCannyThreshold;

	// For Morphological Operation
	Mat k;

	// Hough Transform
	double rho;
	double theta;
	int threshold_hough;
	double minLinLength;
	double maxLineGap;

	// Steigungen
	double steigung;
	double steigung_left;
	double y_achsenabschnitt_left;
	double x_Schnitt_left;
	double steigung_right;
	double y_achsenabschnitt_right;
	double x_Schnitt_right;
		
	bool noLineLeft;
	bool noLineRight;

	// Vektoren fuer erkannte Koordinaten
	vector<Vec4i> lines;
	vector<Vec4i> lines_left;
	vector<Vec4i> lines_right;
	Vec4i left;
	Vec4i right;
	Vec4i middle;

	// Farbe Fahrbahnmarkierung
	Scalar left_Color;
	Scalar right_Color;
	Scalar middle_Color;

public:
//	extern int IMAGEWIDTH;
//	extern int IMAGEHEIGHT;

	lanedetection(Mat);
    ~lanedetection();

	Mat getEdgeImage();
	Mat getLaneImage();
	Vec4i getLeft();
	Vec4i getRight();
	Vec4i getMiddle();
	int getSteeringAngle();

	double getSteigungLeft();
	double getSteigungRight();
	double getSteigungMiddle();

	bool getNoLineLeft();
	bool getNoLineRight();
};

#endif	// LANEDETECTION_H_
