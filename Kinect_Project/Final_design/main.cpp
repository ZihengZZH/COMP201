#include <iostream>
#include <string>
#include <tchar.h>
#include <Kinect.h>
#include <Windows.h>
#include <ShlObj.h>
#include <shellapi.h>

#include <opencv2/opencv.hpp>
#include <wrl/client.h>

#include <Eigen/Core>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <vtkPolyDataMapper.h>
#include <pcl/PolygonMesh.h>

#include "app.h"


// Convenient typedef
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointNT, PointNT, FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerT;


// Global variables
int user_data;
float leaf_size = 0.05f; // Default 0.005f
int RANSAC = 50000; // Default 50000
int noOfSample = 3; // Default 3
int randomness = 5; // Default 5
float threshold = 0.7f; // Default 0.9f
float inlinerFrac = 0.15f; // Default 0.25f
float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
std::string object_name = "kinect_scan.pcd";
std::string scene_name = "IfcOpenHouse.pcd";

// Functions
void displayBackground();
void displayIFC2OBJ();
void displayPointCloud(std::string file_name);
void viewerPsycho(pcl::visualization::PCLVisualizer& viewer);
void IFC2OBJ();
void OBJ2PCD();
bool poseEstimation();
void changeParameters();


int main()
{

	
	// Step 1 IFC2PCD
	displayBackground();
	displayIFC2OBJ();
	IFC2OBJ();
	OBJ2PCD();
	// displayPointCloud("IfcOpenHouse.pcd");
	Sleep(2000);
	system("CLS");
	

	// Step 2 Kinect2PCD
	displayBackground();
	try {
		Kinect kinect;
		kinect.run();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	Sleep(2000);
	system("CLS");

	// Step 3 Pose estimation
	displayBackground();
	while (!poseEstimation()) {
		changeParameters();
		system("CLS");
		displayBackground();
	}
	
	pcl::console::print_info("\nRoll angle %6.3f ", roll);
	pcl::console::print_info("\tPitch angle %6.3f ", pitch);
	pcl::console::print_info("\tYaw angle %6.3f \n", yaw);
	
	system("pause");

	return 0;
}


void displayBackground() {
	std::cout << "------------------------------------" << std::endl;
	std::cout << "            Kinect project         " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << " main libraries & dependencies  " << std::endl;
	std::cout << "  * Kinect v2" << std::endl;
	std::cout << "  * PCL 1.8.0" << std::endl;
	std::cout << "  * OpenCV 3.2.0" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << std::endl;
}


void displayIFC2OBJ() {
	std::cout << "------------------------------------" << std::endl;
	std::cout << "              IFC to OBJ            " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << " Please input as follows: " << std::endl;
	std::cout << " 'IfcConvert IfcOpenHouse.ifc IfcOpenHouse.obj'" << std::endl;
	std::cout << " which will transform IFC file to OBJ file" << std::endl;
	std::cout << " Close command prompt to continue" << std::endl;
	std::cout << std::endl;
}


void displayPointCloud(std::string file_name) {
	std::cout << "Generating point cloud ......" << std::endl;
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::io::loadPCDFile(file_name, *cloud);
	pcl::visualization::CloudViewer viewer("Cloud Viewer");
	
	std::cout << "# of points " << cloud->points.size() << std::endl;

	viewer.showCloud(cloud);
	viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped())
	{
		user_data++;
	}
}


void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
	static unsigned count = 0;
	std::stringstream ss;
	ss << "Once per viewer loop: " << count++;
	viewer.removeShape("text", 0);
	viewer.addText(ss.str(), 200, 300, "text", 0);
	user_data++;
}


void IFC2OBJ() {
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
	ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));

	LPTSTR cmdPath = _T("C:\\Windows\\System32\\cmd.exe");

	if (!CreateProcess(cmdPath, NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &StartupInfo, &ProcessInfo))
	{
		std::cout << "UNABLE TO EXECUTE" << std::endl;
	}
	system("pause");
}


void OBJ2PCD() {
	pcl::PolygonMesh mesh;
	pcl::io::loadPolygonFile("IfcOpenHouse.obj", mesh);

	pcl::PointCloud<pcl::PointXYZ>::Ptr obj_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromPCLPointCloud2(mesh.cloud, *obj_cloud);
	pcl::io::savePCDFileASCII("IfcOpenHouse.pcd", *obj_cloud);

	std::cout << obj_cloud->size() << std::endl;

	std::cout << "Successfully transfromed from OBJ to PCD";
}


bool poseEstimation() {
	// Point clouds
	PointCloudT::Ptr object(new PointCloudT);
	PointCloudT::Ptr object_aligned(new PointCloudT);
	PointCloudT::Ptr scene(new PointCloudT);
	FeatureCloudT::Ptr object_features(new FeatureCloudT);
	FeatureCloudT::Ptr scene_features(new FeatureCloudT);


	// Load object and scene
	pcl::console::print_highlight("Loading point clouds...\n");
	if (pcl::io::loadPCDFile<PointNT>(object_name, *object) < 0 ||
		pcl::io::loadPCDFile<PointNT>(scene_name, *scene) < 0)
	{
		pcl::console::print_error("Error loading object/scene file!\n");
		return false;
	}

	// Downsample
	pcl::console::print_highlight("Downsampling...\n");
	pcl::VoxelGrid<PointNT> grid;
	const float leaf = leaf_size; // 5mm
	grid.setLeafSize(leaf, leaf, leaf);
	grid.setInputCloud(object);
	grid.filter(*object);
	grid.setInputCloud(scene);
	grid.filter(*scene);

	// Estimate normals for scene
	pcl::console::print_highlight("Estimating scene normals...\n");
	pcl::NormalEstimationOMP<PointNT, PointNT> nest;
	nest.setNumberOfThreads(2);
	nest.setRadiusSearch(0.01);
	nest.setInputCloud(scene);
	nest.compute(*scene);

	// Estimate features
	pcl::console::print_highlight("Estimating features...\n");
	FeatureEstimationT fest;
	fest.setNumberOfThreads(2);
	fest.setRadiusSearch(0.025);
	fest.setInputCloud(object);
	fest.setInputNormals(object);
	fest.compute(*object_features);
	fest.setInputCloud(scene);
	fest.setInputNormals(scene);
	fest.compute(*scene_features);

	// Perform alignment
	pcl::console::print_highlight("Starting alignment...\n");
	pcl::SampleConsensusPrerejective<PointNT, PointNT, FeatureT> align;
	align.setInputSource(object);
	align.setSourceFeatures(object_features);
	align.setInputTarget(scene);
	align.setTargetFeatures(scene_features);
	align.setMaximumIterations(RANSAC); // Number of RANSAC iterations
	align.setNumberOfSamples(noOfSample); // Number of points to sample for generating/prerejecting a pose
	align.setCorrespondenceRandomness(randomness); // Number of nearest features to use
	align.setSimilarityThreshold(threshold); // Polygonal edge length similarity threshold
	align.setMaxCorrespondenceDistance(2.5f * leaf); // Inlier threshold
	align.setInlierFraction(inlinerFrac); // Required inlier fraction for accepting a pose hypothesis
	{
		pcl::ScopeTime t("Alignment");
		align.align(*object_aligned);
	}

	if (align.hasConverged())
	{
		// Print results
		printf("\n");
		Eigen::Matrix4f transformation = align.getFinalTransformation();
		pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n", transformation(0, 0), transformation(0, 1), transformation(0, 2));
		pcl::console::print_info("R = | %6.3f %6.3f %6.3f | \n", transformation(1, 0), transformation(1, 1), transformation(1, 2));
		pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n", transformation(2, 0), transformation(2, 1), transformation(2, 2));
		pcl::console::print_info("\n");
		pcl::console::print_info("t = < %0.3f, %0.3f, %0.3f >\n", transformation(0, 3), transformation(1, 3), transformation(2, 3));
		pcl::console::print_info("\n");
		pcl::console::print_info("Inliers: %i/%i\n", align.getInliers().size(), object->size());

		Eigen::Affine3f rotation;
		rotation.matrix() = transformation;
		pcl::getEulerAngles(rotation, roll, pitch, yaw);

		// Show alignment
		pcl::visualization::PCLVisualizer visu("Alignment");
		visu.addPointCloud(scene, ColorHandlerT(scene, 0.0, 255.0, 0.0), "scene");
		visu.addPointCloud(object_aligned, ColorHandlerT(object_aligned, 0.0, 0.0, 255.0), "object_aligned");
		visu.spin();
	}
	else
	{
		pcl::console::print_error("Alignment failed!\n");
		Sleep(1000);
		return false;
	}
	Sleep(500);
	return true;
}


void changeParameters() {
	int input;
	double leafsz, thes, infrac;
	std::cout << "Some parameters may lead to alignment failure" << std::endl;
	std::cout << "Choose one of the following to modify" << std::endl;
	std::cout << "0. Leaf size for downsample (Default 0.005f)" << std::endl;
	std::cout << "1. Polygonal edge length similarity threshold (Default 0.9f)" << std::endl;
	std::cout << "2. Required inlier fraction for accepting a pose hypothesis (Default 0.25f)" << std::endl;
	std::cout << "Which one would you like to modify?" << std::endl;
	std::cin >> input;
	std::cout << "Please input modified value" << std::endl;
	if (input == 0) {
		std::cin >> leafsz;
		leaf_size = (float)leafsz;
	}
	else if (input == 1) {
		std::cin >> thes;
		threshold = (float)thes;
	}
	else if (input == 2) {
		std::cin >> infrac;
		inlinerFrac = (float)infrac;
	}
	else {
		std::cout << "Invalid input" << std::endl;
	}

	std::cout << "Leaf Size " << leaf_size << "  Threshold " << threshold << "  Inliner fraction " << inlinerFrac << std::endl;
}


/*
Parameters for robust pose estimation of rigid objects
	leaf = 0.01f
	setMaximumIterations(50000)
	setNumberOfSamples(3)
	setCorrespondenceRandomness(5)
	setSimilarityThreshold(0.9f)
	setMaxCorrespondenceDistance(2.5f * leaf)
	setInlierFraction(0.4f)
These parameters are adjustable and some may leads to alignment failure
*/
