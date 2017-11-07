#include <iostream>
#include <fstream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>

using namespace cv;
using namespace std;

int main() {


	Mat3b camera_mat1, camera_mat2;
	Mat rview1, map1, map2;
	Mat rview2, map3, map4;
	Mat img, imgLeft, imgRight, output;
	double minVal, maxVal;
	Size size(768, 576);

	imgLeft = imread("test_L.png", IMREAD_GRAYSCALE);
	imgRight = imread("test_R.png", IMREAD_GRAYSCALE);
	resize(imgLeft, imgLeft, size);
	resize(imgRight, imgRight, size);


	// These parameters should be adjusted to specific cameras
	//int ndisparities = 128, SADWindowSize = 9;
	//Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	int ndisparities = 144, SADWindowSize = 3, mindisparity = 0;
	Ptr<StereoSGBM> sbm = StereoSGBM::create(mindisparity,ndisparities,SADWindowSize,216,864,1,63,0,100,32);

	/*
	There is a huge difference between BM algorithm and SGBM algorithm
	The implementation of BM is quick with satisfactory resolution
	But the implementation of SGBM has finer resolution at the expense of low speed
	*/


	Mat imgDisparity16S = Mat(imgLeft.rows, imgLeft.cols, CV_16S);
	Mat imgDisparity8U = Mat(imgLeft.rows, imgLeft.cols, CV_8UC1);

	// Compute disparity map for the specified stereo pair
	sbm->compute(imgLeft, imgRight, imgDisparity16S);
	minMaxLoc(imgDisparity16S, &minVal, &maxVal);
	cout << "Min disp " << minVal << " Max disp " << maxVal << endl;
	imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));

	Mat disp, disp8, points;
	sbm->compute(imgLeft, imgRight, disp);

	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

	imshow("Left view", imgLeft);
	imshow("Right view", imgRight);
	imshow("Disparity map", disp8);
	// Show disp8 or imgDisparity8U

	waitKey();

	
	// Knowing the intrinsics parameters of the camera is crucial if an accurate 3D reconstruction is required
	// Therefore, without matrix Q, the reconstruction could not be completed 
	/*reprojectImageTo3D(disp, points, Q, true);

	ofstream point_cloud_file;
	point_cloud_file.open("point_cloud.xyz");
	for (int i = 0; i < points.rows; i++) {
		for (int j = 0; j < points.cols; j++) {
			if (points.at<Vec3f>(i, j)[2] < 10) {
				point_cloud_file << points.at<Vec3f>(i, j)[0] << " " << points.at<Vec3f>(i, j)[1] << " " << points.at<Vec3f>(i, j)[2]
					<< " " << static_cast<unsigned>(imgLeft.at<uchar>(i, j)) << " " << static_cast<unsigned>(imgLeft.at<uchar>(i, j))
					<< " " << static_cast<unsigned>(imgLeft.at<uchar>(i, j)) << endl;
				//pointspcd.push_back({points.at<Vec3f>(i,j)[0],points.at<Vec3f>(i,j)[1],points.at<Vec3f>(i,j)[2]});
			}
		}
	}
	point_cloud_file.close();*/


	return 0;

}

