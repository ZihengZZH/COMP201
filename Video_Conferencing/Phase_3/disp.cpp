#include <stdio.h>
#include <string>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\calib3d\calib3d.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>


using namespace std;
using namespace cv;


/*
Parameters:
numDisparities: the disparity search range. For each pixel algorithm will find
		the best disparity from 0 (default minimum disparity) to numDisparities. The search range
		can then be shifted by changing the minimum disparity. Also it should be divisible by 16.
blockSize: the linear size of the blocks compared by the algorithm. The size should be odd
		(as the block is centered at the current pixel). Larger block size implies smoother,
		though less accurate disparity map. Smaller block size gives more detailed
		disparity map, but there is higher chance for algorithm to find a wrong correspendence.
*/


int main() {

	VideoCapture camera1(1);
	VideoCapture camera2(0);
	if (!camera1.isOpened()) cout << "Failed to open camera C920\n";
	if (!camera2.isOpened()) cout << "Failed to open camera C920\n";
	camera1.set(CV_CAP_PROP_FRAME_WIDTH, 540);
	camera1.set(CV_CAP_PROP_FRAME_HEIGHT, 360);
	camera2.set(CV_CAP_PROP_FRAME_WIDTH, 540);
	camera2.set(CV_CAP_PROP_FRAME_HEIGHT, 360);

	Mat3b camera_mat1, camera_mat2;
	Mat rview1, map1, map2;
	Mat rview2, map3, map4;
	Mat img, imgLeft, imgRight, output;
	double minVal, maxVal;

	// These parameters should be adjusted to specific cameras
	int ndisparities = 128, SADWindowSize = 9; 
	Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	//int ndisparities = 32, SADWindowSize = 15;
	//Ptr<StereoSGBM> sbm = StereoSGBM::create(-39,ndisparities,SADWindowSize,0,0,1,63,0,100,32);
	
	/*
	There is a huge difference between BM algorithm and SGBM algorithm
	The implementation of BM is quick with satisfactory resolution
	But the implementation of SGBM has finer resolution at the expense of low speed
	*/
	
	/*img = imread("test.jpg", CV_BayerBG2GRAY);
	int height = img.rows, width = img.cols;
	int crop = width / 2;

	Rect roiL, roiR;
	roiL.x = 0;
	roiL.y = 0;
	roiL.width = crop;
	roiL.height = height;
	roiR.x = crop;
	roiR.y = 0;
	roiR.width = crop;
	roiR.height = height;*/

	/*
	imgLeft = imread("imageLeft.png", IMREAD_GRAYSCALE);
	imgRight = imread("imageRight.png", IMREAD_GRAYSCALE);
	imgLeft = imread("test1.jpg", IMREAD_GRAYSCALE);
	imgRight = imread("test2.jpg", IMREAD_GRAYSCALE);

	imgLeft = img(roiL);
	imgRight = img(roiR);

	Mat imgDisparity16S = Mat(imgLeft.rows, imgLeft.cols, CV_16S);
	Mat imgDisparity8U = Mat(imgLeft.rows, imgLeft.cols, CV_8UC1);

	Compute disparity map for the specified stereo pair
	sbm->compute(imgLeft, imgRight, imgDisparity16S);
	minMaxLoc(imgDisparity16S, &minVal, &maxVal);
	cout << "Min disp " << minVal << " Max disp " << maxVal << endl;
	imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));

	imshow("Left view", imgLeft);
	imshow("Right view", imgRight);
	imshow("Disparity map", imgDisparity8U);

	waitKey();*/

	while (1) {
		camera1 >> camera_mat1;
		camera2 >> camera_mat2;
		Size imageSize1 = camera_mat1.size();
		Size imageSize2 = camera_mat2.size();

		Mat imgDisparity16S = Mat(camera_mat1.rows, camera_mat1.cols, CV_16S);
		Mat imgDisparity8U = Mat(camera_mat1.rows, camera_mat1.cols, CV_8UC1);

		Mat imgLeft, imgRight;
		cvtColor(camera_mat1, imgLeft, CV_RGB2GRAY);
		cvtColor(camera_mat2, imgRight, CV_RGB2GRAY);

		sbm->compute(imgLeft, imgRight, imgDisparity16S);
		minMaxLoc(imgDisparity16S, &minVal, &maxVal);
		cout << "Min disp " << minVal << " Max disp " << maxVal << endl;
		imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255 / (maxVal - minVal));

		cv::imshow("Calibrated view of C920-0", camera_mat1);
		cv::imshow("Calibrated view of C920-1", camera_mat2);
		cv::imshow("window Disparity", imgDisparity8U);

		//reprojectImageTo3D(imgDisparity8U, output, Mat());



		int c = cvWaitKey(1);
		if (27 == char(c)) break;
	}
	
	return 0;

}



/*

EFFECT MEANS HOW WELL THE DISPARITY MAP LOOKS (BM)

	#disp		SAD			EFFECT
	128			9			6
	128			11			6			
	64			21			4
	64			11			5
	64			9			5
	32			11			5
	32			9			4

*/


/*

EFFECT MEANS HOW WELL THE DISPARITY MAP LOOKS (SGBM)

	#disp		SAD			EFFECT
	64			21			3

the implementation of SGBM is too slow to be accepted in the project

*/