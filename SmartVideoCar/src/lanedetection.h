#ifndef LANEDETECTION_H
#define LANEDETECTION_H

class lanedetection
{
private:
    Mat frame_roi;
    Mat img_gray;
    Mat img_edges;
    Mat img_lines;
    int roi_x;
	int roi_y;
	int roi_width;
	int roi_height;
	Rect region_of_interest;
	
	// Canny
	int minCannyThreshold;
	int maxCannyThreshold;
	
	// Morphological Operation
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
	
	int counter_left;
	int counter_right;
	
	// Vektoren für erkannte Koordinaten
	vector<Vec4i> lines;
	Vec4i left;
	Vec4i right;
	
	// Distanz zum Fahrbahnrand
	int distance_L;
	int distance_R;
	
	// Farbe Fahrbahnmarkierung
	Scalar left_Color;
	Scalar right_Color;
	
public:
	lanedetection(Mat frame);
    ~lanedetection();
    
	Mat getEdgeImage();
	Mat getLaneImage();
	string getStringDistance();
};

#endif	// LANEDETECTION_H