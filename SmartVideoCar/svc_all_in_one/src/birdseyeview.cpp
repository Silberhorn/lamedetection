#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "birdseyeview.h"

using namespace std;
using namespace cv;

birdseyeview::birdseyeview(Mat imgSource, int alpha_, int focalLength, int dist)
{
	this->imgSource = imgSource;
	this->alpha_ = alpha_;
	this->focalLength = focalLength;
	this->dist = dist;

	alpha =((double)alpha_ - 90) * CV_PI / 180;
	beta = 0.0;
	gamma = 0.0;

	Size image_size = imgSource.size();
	w = (double)image_size.width;
	h = (double)image_size.height;

	// Projection matrix 2D -> 3D
	A1 = (Mat_<float>(4, 3) << 
		1, 0, -w/2,
		0, 1, -h/2,
		0, 0, 0,
		0, 0, 1 );

	// Rotation matrices Rx, Ry, Rz
	RX = (Mat_<float>(4, 4) << 
		1, 0, 0, 0,
		0, cos(alpha), -sin(alpha), 0,
		0, sin(alpha), cos(alpha), 0,
		0, 0, 0, 1 );

	RY = (Mat_<float>(4, 4) << 
		cos(beta), 0, -sin(beta), 0,
		0, 1, 0, 0,
		sin(beta), 0, cos(beta), 0,
		0, 0, 0, 1 );

	RZ = (Mat_<float>(4, 4) << 
		cos(gamma), -sin(gamma), 0, 0,
		sin(gamma), cos(gamma), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 );

	// R - rotation matrix
	R = RX * RY * RZ;

	// T - translation matrix
	T = (Mat_<float>(4, 4) << 
		1, 0, 0, 0,  
		0, 1, 0, 0,  
		0, 0, 1, dist,  
		0, 0, 0, 1 ); 
	
	// K - intrinsic matrix 
	K = (Mat_<float>(3, 4) << 
		focalLength, 0, w/2, 0,
		0, focalLength, h/2, 0,
		0, 0, 1, 0 ); 

	transformationMat = K * (T * (R * A1));

	warpPerspective(imgSource, birdImg, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);
}

birdseyeview::~birdseyeview() {}

Mat birdseyeview::getBirdsEyeView()
{
	return birdImg;
}