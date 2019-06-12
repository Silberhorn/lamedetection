// OpenCV imports
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// C++ imports
#include <iostream>

// namespaces
using namespace std;
using namespace cv;
#define PI 3.1415926

Mat frame, frame2;

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

/*
 * This code illustrates bird's eye view perspective transformation using opencv
 * Paper: Distance Determination for an Automobile Environment using Inverse Perspective Mapping in OpenCV  
 * Link to paper: https://www.researchgate.net/publication/224195999_Distance_determination_for_an_automobile_environment_using_Inverse_Perspective_Mapping_in_OpenCV
 * Code taken from: http://www.aizac.info/birds-eye-view-homography-using-opencv/
 */ 

int main()
{
	Mat source, destination;

	int alpha_ = 96;
	int f_ = 10, dist_ = 10;

	namedWindow("Result");
	namedWindow("frame");
	moveWindow("frame", 10, 50);

	createTrackbar("Alpha", "Result", &alpha_, 180);
	createTrackbar("f", "Result", &f_, 2000);
	createTrackbar("Distance", "Result", &dist_, 2000);

	frame = imread("./pipicture.jpg");

	if(frame.empty()) {
		cout << "capture error\n" << endl;
	}

	frame2 = birdsEyeView(frame, 12, 500, 500);		// 90, 500, 500
	imshow("frame", frame2);

	while( true ) {
		
		source = frame2;

		double focalLength, dist, alpha, beta, gamma; 

		alpha =((double)alpha_ -90) * PI/180;
		focalLength = (double)f_;
		dist = (double)dist_;

		Size image_size = source.size();
		double w = (double)image_size.width, h = (double)image_size.height;


		// Projecion matrix 2D -> 3D
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
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1	);

		Mat RZ = (Mat_<float>(4, 4) << 
			1, 0, 0, 0,
			0, 1, 0, 0,
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

		warpPerspective(source, destination, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);

		imshow("Result", destination);
		waitKey(1);
	}


	return 0;
}
