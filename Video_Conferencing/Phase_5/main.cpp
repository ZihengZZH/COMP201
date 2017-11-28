#include "utility.h"

using namespace cv;
using namespace std;


int user_data;
const string un1 = "undistort1.jpg";
const string un2 = "undistort2.jpg";

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer) {
	static unsigned count = 0;
	std::stringstream ss;
	ss << "Once per viewer loop: " << count++;
	viewer.removeShape("text", 0);
	viewer.addText(ss.str(), 200, 300, "text", 0);

	user_data++;
}


void disparityMap() {

	Mat3b camera_mat1, camera_mat2;
	Mat rview1, map1, map2;
	Mat rview2, map3, map4;
	Mat img, imgLeft_col, imgRight_col, output;
	Mat imgLeft, imgRight;
	double minVal, maxVal;
	Size size(640, 480);
	Mat Q, M1, M2, D1, D2;

	FileStorage fs;
	fs.open("extrinsics.yml", FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "Failed to open" << endl;
		return;
	}
	fs["Q"] >> Q;

	fs.open("intrinsics.yml", FileStorage::READ);
	if (!fs.isOpened()) {
		cerr << "Failed to open" << endl;
		return;
	}
	fs["M1"] >> M1;
	fs["M2"] >> M2;
	fs["D1"] >> D1;
	fs["D2"] >> D2;

	fs.release();

	VideoCapture camera0(0);
	VideoCapture camera1(1);
	Mat cam_mat1, cam_mat2;
	Mat camera_un1, camera_un2;

	while (true) {
		camera0 >> cam_mat1;
		camera1 >> cam_mat2;
		imshow("Left camera", cam_mat1);
		imshow("Right camera",cam_mat2);
		char key = (char)waitKey(30);
		if (key == ' ') {
			undistort(cam_mat1, camera_un1, M1, D1);
			undistort(cam_mat2, camera_un2, M2, D2);
			imwrite(un1, camera_un1);
			imwrite(un2, camera_un2);
			break;
		}
		if (key == 27) {
			break;
		}
	}

	destroyAllWindows();
	system("pause");
	cout << "Generating disparity map ..." << endl;

	imgLeft_col = imread(un1); // test_L.png
	imgRight_col = imread(un2); // test_R.png

	cvtColor(imgLeft_col, imgLeft, CV_BGR2GRAY);
	cvtColor(imgRight_col, imgRight, CV_BGR2GRAY);

	resize(imgLeft, imgLeft, size);
	resize(imgRight, imgRight, size);

	// These parameters should be adjusted to specific cameras
	//int ndisparities = 128, SADWindowSize = 9;
	//Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	int ndisparities = 144, SADWindowSize = 3, mindisparity = 0;
	Ptr<StereoSGBM> sbm = StereoSGBM::create(mindisparity, ndisparities, SADWindowSize, 216, 864, 1, 63, 0, 100, 32);

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
	imshow("Disparity map", imgDisparity8U);

	waitKey();
	destroyAllWindows();
	system("pause");
	cout << "Generating point cloud ..." << endl;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointcloud(new   pcl::PointCloud<pcl::PointXYZRGB>());
	Mat xyz;
	reprojectImageTo3D(imgDisparity8U, xyz, Q, false, CV_32F);
	pointcloud->width = static_cast<uint32_t>(imgDisparity8U.cols);
	pointcloud->height = static_cast<uint32_t>(imgDisparity8U.rows);
	pointcloud->is_dense = false;
	pcl::PointXYZRGB point;
	for (int i = 0; i < imgDisparity8U.rows; ++i) {
		uchar* rgb_ptr = imgRight_col.ptr<uchar>(i);
		uchar* disp_ptr = imgDisparity8U.ptr<uchar>(i);
		double* xyz_ptr = xyz.ptr<double>(i);

		for (int j = 0; j < imgDisparity8U.cols; ++j) {
			uchar d = disp_ptr[j];
			if (d == 0) continue;
			Point3f p = xyz.at<Point3f>(i, j);
			point.z = p.z;
			point.x = p.x;
			point.y = p.y;

			point.b = rgb_ptr[3 * j];
			point.g = rgb_ptr[3 * j + 1];
			point.r = rgb_ptr[3 * j + 2];
			pointcloud->points.push_back(point);
		}
	}

	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	viewer.showCloud(pointcloud);
	viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped()) {
		user_data++;
	}

	// Knowing the intrinsics/extrinsics parameters of the camera is crucial if an accurate 3D reconstruction is required
	// Therefore, without matrix Q, the reconstruction could not be completed 

}


int main() {

	Calibrate* start = new Calibrate();
	start->stereoCal();
	disparityMap();
	return 0;

}