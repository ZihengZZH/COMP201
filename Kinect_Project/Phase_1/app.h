#ifndef __APP__
#define __APP__

#include <Windows.h>
#include <Kinect.h>
#include <opencv2/opencv.hpp>

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

    // Reader
    ComPtr<IColorFrameReader> colorFrameReader;
	ComPtr<IBodyIndexFrameReader> bodyIndexFrameReader;
	ComPtr<IDepthFrameReader> depthFrameReader;

    // Color Buffer
    std::vector<BYTE> colorBuffer;
    int colorWidth;
    int colorHeight;
    unsigned int colorBytesPerPixel;
    cv::Mat colorMat;
	
	// BodyIndex Buffer
	std::vector<BYTE> bodyIndexBuffer;
	int bodyIndexWidth;
	int bodyIndexHeight;
	unsigned int bodyIndexBytesPerPixel;
	cv::Mat bodyIndexMat;
	std::array<cv::Vec3b, BODY_COUNT> colors;

	// Depth Buffer
	std::vector<UINT16> depthBuffer;
	int depthWidth;
	int depthHeight;
	unsigned int depthBytesPerPixel;
	cv::Mat depthMat;

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

	// Initialize BodyIndex
	inline void initializeBodyIndex();

	// Initialize Depth
	inline void initializeDepth();

    // Finalize
    void finalize();

    // Update Data
    void update();

    // Update Color
    inline void updateColor();

	// Update BodyIndex
	inline void updateBodyIndex();

	// Update Depth
	inline void updateDepth();

    // Draw Data
    void draw();

    // Draw Color
    inline void drawColor();

	// Draw BodyIndex
	inline void drawBodyIndex();

	// Draw Depth
	inline void drawDepth();

    // Show Data
    void show();

    // Show Color
    inline void showColor();

	// Show BodyIndex
	inline void showBodyIndex();

	// Show Depth
	inline void showDepth();

	// Get Depth Data
	void getDepthData();

	// Calculate the average inside a vector
	int calculateAverage(std::vector<int>& nums);

	// Convert data structure from float to string
	std::string convert(float num);
};

#endif // __APP__