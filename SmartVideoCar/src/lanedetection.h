#ifndef LANEDETECTION_H
#define LANEDETECTION_H

class lanedetection
{
private:

	
public:
	lanedetection(Mat frame);
    ~lanedetection();
    
	Mat getEdgeImage();
	Mat getLaneImage();
	Vec4i getLeft();
	Vec4i getRight();
};

#endif	// LANEDETECTION_H
