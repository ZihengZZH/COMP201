#ifndef __APP__
#define __APP__

#include <Windows.h>
#include <Kinect.h>
#include <opencv2/opencv.hpp>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <vector>
#include <array>
#include <sstream>

#include <wrl/client.h>
using namespace Microsoft::WRL;

class Kinect
{
private:
    // Sensor
    ComPtr<IKinectSensor> kinect;

	// Coordinate Mapper
	ComPtr<ICoordinateMapper> coordinateMapper;

    // Reader
    ComPtr<IColorFrameReader> colorFrameReader;
	ComPtr<IDepthFrameReader> depthFrameReader;

    // Color Buffer
    std::vector<BYTE> colorBuffer;
    int colorWidth;
    int colorHeight;
    unsigned int colorBytesPerPixel;
    cv::Mat colorMat;

	// Depth Buffer
	std::vector<UINT16> depthBuffer;
	int depthWidth;
	int depthHeight;
	unsigned int depthBytesPerPixel;
	cv::Mat depthMat;

	// PCL 
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;

	// Other attributes 
	int frameCount;
	float distanceF;
	std::string text, temp;

public:
    // Constructor
    Kinect();

    // Destructor
    ~Kinect();

    // Processing
    void run();

private:
    // Initialize
    void initialize();

    // Initialize Sensor
    inline void initializeSensor();

    // Initialize Color
    inline void initializeColor();

	// Initialize Depth
	inline void initializeDepth();

	// Initialize Point Cloud
	inline void initializePointCloud();

    // Finalize
    void finalize();

    // Update Data
    void update();

    // Update Color
    inline void updateColor();

	// Update Depth
	inline void updateDepth();

	// Update Point Cloud
	inline void updatePointCloud();

    // Draw Data
    void draw();

    // Draw Color
    inline void drawColor();

	// Draw Depth
	inline void drawDepth();

	// Draw Point Cloud
	inline void drawPointCloud();

    // Show Data
    void show();

    // Show Color
    inline void showColor();

	// Show Depth
	inline void showDepth();

	// Show Point Cloud
	inline void showPointCloud();
	
	// Save Point Cloud to File
	void savePointCloud();

	// Get Depth Data
	void getDepthData();

	// Calculate the average inside a vector
	int calculateAverage(std::vector<int>& nums);

	// Convert data structure from float to string
	std::string convert(float num);
};

#endif // __APP__