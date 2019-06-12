#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

Mat frame1, frame2, frame3;

Mat birdsEyeView(Mat imgSource, int alpha_, int focalLength, int dist) {
		Mat birdImg;
		double alpha, beta, gamma; 

		alpha =((double)alpha_ -90) * CV_PI/180;
		beta = 0.0;
		gamma = 0.0;

		Size image_size = imgSource.size();
		double w = (double)image_size.width, h = (double)image_size.height;


		// Projection matrix 2D -> 3D
		Mat A1 = (Mat_<float>(4, 3)<< 
			1, 0, -w/2,
			0, 1, -h/2,
			0, 0, 0,
			0, 0, 1 );

	
		// Rotation matrices Rx, Ry, Rz

		Mat RX = (Mat_<float>(4, 4) << 
			1, 0, 0, 0,
			0, cos(alpha), -sin(alpha), 0,
			0, sin(alpha), cos(alpha), 0,
			0, 0, 0, 1 );

		Mat RY = (Mat_<float>(4, 4) << 
			cos(beta), 0, -sin(beta), 0,
			0, 1, 0, 0,
			sin(beta), 0, cos(beta), 0,
			0, 0, 0, 1	);

		Mat RZ = (Mat_<float>(4, 4) << 
			cos(gamma), -sin(gamma), 0, 0,
			sin(gamma), cos(gamma), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1	);


		// R - rotation matrix
		Mat R = RX * RY * RZ;

		// T - translation matrix
		Mat T = (Mat_<float>(4, 4) << 
			1, 0, 0, 0,  
			0, 1, 0, 0,  
			0, 0, 1, dist,  
			0, 0, 0, 1); 
		
		// K - intrinsic matrix 
		Mat K = (Mat_<float>(3, 4) << 
			focalLength, 0, w/2, 0,
			0, focalLength, h/2, 0,
			0, 0, 1, 0
			); 


		Mat transformationMat = K * (T * (R * A1));

		warpPerspective(imgSource, birdImg, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);

		return birdImg;
}

int main()
{	
	// Open Windows for Image Display
	namedWindow("frame1");
	moveWindow("frame1", 10, 50);
	namedWindow("frame2");
	moveWindow("frame2", 410, 100);
	namedWindow("frame3");
	moveWindow("frame3", 810, 150);

	frame1 = imread("./pipicture.jpg");

	if(frame1.empty()) {
		cout << "capture error\n" << endl;
	}

	imshow("frame1", frame1);
	
	frame2 = birdsEyeView(frame1, 12, 500, 500);		// 8, 790, 1038	// 90, 500, 500
	imshow("frame2", frame2);
	
	frame3 = birdsEyeView(frame2, 90+78, 500, 500);
	imshow("frame3", frame3);

	waitKey(0);

	return 0;
}
