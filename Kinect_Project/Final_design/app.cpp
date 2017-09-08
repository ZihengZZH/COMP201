#include "app.h"
#include "util.h"

#include <thread>
#include <chrono>


// Constructor
Kinect::Kinect()
{
    // Initialize
    initialize();
}


// Destructor
Kinect::~Kinect()
{
    // Finalize
    finalize();
}

// Processing
void Kinect::run()
{
	std::cout << std::endl;
	int count = 0;
	std::string output;
    // Main Loop
    while( !viewer->wasStopped() ){

        // Update Data
        update();

        // Draw Data
        draw();

        // Show Data
        show();

		// Get & print depth data
		// getDepthData();

        // Key Check
		/*const int key = cv::waitKey( 10 );
        if( key == VK_ESCAPE ){
            break;
        }*/

		switch (count % 3) {
		case 0:
			output = " ..    ";
			break;
		case 1:
			output = " ....  ";
			break;
		case 2:
			output = " ......";
			break;
		}
		std::cout << "\rClose point cloud viewer to exit ans save pcd file " << output;

		count++;
    }

	savePointCloud();
}


// Initialize
void Kinect::initialize()
{
    cv::setUseOptimized( true );

	frameCount = 0;

    // Initialize Sensor
    initializeSensor();

    // Initialize Color
    initializeColor();

	// Initialize Depth
	initializeDepth();

	// Initialize Point Cloud
	initializePointCloud();

    // Wait a Few Seconds until begins to Retrieve Data from Sensor ( about 2000-[ms] )
    std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
}


// Initialize Sensor
inline void Kinect::initializeSensor()
{
    // Open Sensor
    ERROR_CHECK( GetDefaultKinectSensor( &kinect ) );

	std::cout << "Initializing Kinect ......." << std::endl;
    ERROR_CHECK( kinect->Open() );

    // Check Open
    BOOLEAN isOpen = FALSE;
    ERROR_CHECK( kinect->get_IsOpen( &isOpen ) );
    if( !isOpen ){
        throw std::runtime_error( "failed IKinectSensor::get_IsOpen( &isOpen )" );
    }

	// Retrieve Coordinate Mapper
	ERROR_CHECK(kinect->get_CoordinateMapper(&coordinateMapper));
	std::cout << "Initializing completed" << std::endl;
}


// Initialize Color
inline void Kinect::initializeColor()
{
    // Open Color Reader
    ComPtr<IColorFrameSource> colorFrameSource;
    ERROR_CHECK( kinect->get_ColorFrameSource( &colorFrameSource ) );
    ERROR_CHECK( colorFrameSource->OpenReader( &colorFrameReader ) );

    // Retrieve Color Description
    ComPtr<IFrameDescription> colorFrameDescription;
    ERROR_CHECK( colorFrameSource->CreateFrameDescription( ColorImageFormat::ColorImageFormat_Bgra, &colorFrameDescription ) );
    ERROR_CHECK( colorFrameDescription->get_Width( &colorWidth ) ); // 1920
    ERROR_CHECK( colorFrameDescription->get_Height( &colorHeight ) ); // 1080
    ERROR_CHECK( colorFrameDescription->get_BytesPerPixel( &colorBytesPerPixel ) ); // 4

    // Allocation Color Buffer
    colorBuffer.resize( colorWidth * colorHeight * colorBytesPerPixel );
}


// Initialize Depth
inline void Kinect::initializeDepth() 
{
	// Open Depth Reader
	ComPtr<IDepthFrameSource> depthFrameSource;
	ERROR_CHECK(kinect->get_DepthFrameSource(&depthFrameSource));
	ERROR_CHECK(depthFrameSource->OpenReader(&depthFrameReader));

	// Retrieve Depth Description
	ComPtr<IFrameDescription> depthFrameDescription;
	ERROR_CHECK(depthFrameSource->get_FrameDescription(&depthFrameDescription));
	ERROR_CHECK(depthFrameDescription->get_Width(&depthWidth)); // 512
	ERROR_CHECK(depthFrameDescription->get_Height(&depthHeight)); // 424
	ERROR_CHECK(depthFrameDescription->get_BytesPerPixel(&depthBytesPerPixel)); // 2

	// Retrieve Depth Reliable Range
	UINT16 minReliableDistance;
	UINT16 maxReliableDistance;
	ERROR_CHECK(depthFrameSource->get_DepthMinReliableDistance(&minReliableDistance)); // 500
	ERROR_CHECK(depthFrameSource->get_DepthMaxReliableDistance(&maxReliableDistance)); // 4500
	std::cout << "Depth Reliable Range : " << minReliableDistance << " - " << maxReliableDistance << std::endl;

	// Allocation Depth Buffer
	depthBuffer.resize(depthWidth * depthHeight);
}


// Initialize Point Cloud
inline void Kinect::initializePointCloud()
{
	// Create Point Cloud
	cloud = boost::make_shared<pcl::PointCloud<pcl::PointXYZRGBA>>();
	cloud->width = static_cast<uint32_t>(depthWidth)/2; // Set as half points
	cloud->height = static_cast<uint32_t>(depthHeight)/2;
	cloud->points.resize(cloud->height*cloud->width);
	cloud->is_dense = false;

	// Create PCLVisualizer
	viewer = boost::make_shared<pcl::visualization::PCLVisualizer>("Point Cloud Viewer");

	// Initialize camera position along with orientation
	viewer->setCameraPosition(0.0, 0.0, -2.5, 0.0, 0.0, 0.0);

	// Add Coordinate System
	viewer->addCoordinateSystem(0.1);
}


// Finalize
void Kinect::finalize()
{
    cv::destroyAllWindows();

    // Close Sensor
    if( kinect != nullptr ){
        kinect->Close();
    }
}


// Update Data
void Kinect::update()
{
    // Update Color
    updateColor();

	// Update Depth
	updateDepth();

	// Update Point Cloud
	updatePointCloud();
}


// Update Color
inline void Kinect::updateColor()
{
    // Retrieve Color Frame
    ComPtr<IColorFrame> colorFrame;
    const HRESULT ret = colorFrameReader->AcquireLatestFrame(&colorFrame);
    if(FAILED(ret)){
        return;
    }

    // Convert Format ( YUY2 -> BGRA )
    ERROR_CHECK( colorFrame->CopyConvertedFrameDataToArray(static_cast<UINT>(colorBuffer.size() ), 
		&colorBuffer[0], ColorImageFormat::ColorImageFormat_Bgra));
}


// Update Depth
inline void Kinect::updateDepth() {
	// Retrieve Depth Frame
	ComPtr<IDepthFrame> depthFrame;
	const HRESULT ret = depthFrameReader->AcquireLatestFrame(&depthFrame);
	if (FAILED(ret)) {
		return;
	}

	// Retrieve Depth Data
	ERROR_CHECK(depthFrame->CopyFrameDataToArray(static_cast<UINT>(depthBuffer.size()), &depthBuffer[0]));
}


// Update Point Cloud
inline void Kinect::updatePointCloud()
{
	// Reset Point Cloud
	cloud->clear();

	// Convert to Point Cloud
	#pragma omp parallel for
	for (int depthY = 0; depthY < depthHeight/2; depthY++) { // Set as half points
		for (int depthX = 0; depthX < depthWidth/2; depthX++) {
			pcl::PointXYZRGBA point;

			// Retrieve Mapped Coordinates
			DepthSpacePoint depthSpacePoint = { static_cast<float>(depthX),static_cast<float>(depthY) };
			UINT16 depth = depthBuffer[depthY*depthWidth*2 + depthX*2];
			ColorSpacePoint colorSpacePoint = { 0.0f,0.0f };
			ERROR_CHECK(coordinateMapper->MapDepthPointToColorSpace(depthSpacePoint, depth, &colorSpacePoint));

			//Set Color to Point
			int colorX = static_cast<int>(colorSpacePoint.X + 0.5f);
			int colorY = static_cast<int>(colorSpacePoint.Y + 0.5f);
			
			if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)) 
			{
				/*unsigned int colorIndex = (colorY*colorWidth*2 + colorX*2)*colorBytesPerPixel;
				point.b = colorBuffer[colorIndex + 0];
				point.g = colorBuffer[colorIndex + 1];
				point.r = colorBuffer[colorIndex + 2];
				point.a = colorBuffer[colorIndex + 3];*/
				point.r = 0;
				point.g = 182;
				point.b = 182;
			}
			
			// Mapping two buffer with different size (not completed)
			// Colorbuffer[1920*1080] DepthBuffer[512*424]
			

			// Retrieve Mapped Coordinates
			CameraSpacePoint cameraSpacePoint = { 0.0f,0.0f,0.0f };
			ERROR_CHECK(coordinateMapper->MapDepthPointToCameraSpace(depthSpacePoint, depth, &cameraSpacePoint));

			// Set Depth to Point
			if ((0 <= colorX) && (colorX < colorWidth) && (0 <= colorY) && (colorY < colorHeight)) 
			{
				point.x = cameraSpacePoint.X;
				point.y = cameraSpacePoint.Y;
				point.z = cameraSpacePoint.Z;
			}

			// Set Point to Point Cloud
			cloud->push_back(point);
		}
	}

}


// Draw Data
void Kinect::draw()
{
    // Draw Color
    drawColor();

	// Draw Depth
	//drawDepth();

	// Draw Point Cloud
	drawPointCloud();
}


// Draw Color
inline void Kinect::drawColor()
{
    // Create cv::Mat from Color Buffer
    colorMat = cv::Mat( colorHeight, colorWidth, CV_8UC4, &colorBuffer[0] );

}


// Draw Depth
inline void Kinect::drawDepth() 
{
	// Create cv::Mat from Depth Buffer
	depthMat = cv::Mat(depthHeight, depthWidth, CV_16UC1, &depthBuffer[0]);
}


// Draw Point Cloud
inline void Kinect::drawPointCloud()
{
	// Update Point Cloud
	if (!viewer->updatePointCloud(cloud, "cloud")) 
	{
		viewer->addPointCloud(cloud, "cloud");
	}
}


// Show Data
void Kinect::show()
{
    // Show Color
    showColor();

	// Show Depth
	//showDepth();

	// Show Point Cloud
	showPointCloud();
}


// Show Color
inline void Kinect::showColor()
{
    if( colorMat.empty() ){
        return;
    }

    // Resize Image
    cv::Mat resizeMat;
    const double scale = 0.5;
    cv::resize( colorMat, resizeMat, cv::Size(), scale, scale );

    // Show Image
    cv::imshow( "2D image viewer", resizeMat);
}


// Show Depth
inline void Kinect::showDepth() 
{
	if (depthMat.empty()) {
		return;
	}

	// Scaling ( 0-8000 -> 255-0 )
	cv::Mat scaleMat;
	depthMat.convertTo(scaleMat, CV_8U, -255.0 / 8000.0, 255.0);
	//cv::applyColorMap( scaleMat, scaleMat, cv::COLORMAP_BONE );

	// Show Image
	cv::imshow("Depth", scaleMat);
}


// Show Point Cloud
inline void Kinect::showPointCloud()
{
	// Update Viewer
	viewer->spinOnce();
}


// Save Point Cloud to File
void Kinect::savePointCloud() {
	std::cout << "\nWritting point cloud to PCD file, named kinect_scan.pcd\n";
	ERROR_CHECK(pcl::io::savePCDFileASCII("kinect_scan.pcd", *cloud));
	std::cout << "Successfully written to file\n";
}


// Get Depth Data
void Kinect::getDepthData() {

	/*
	depthData = {};

	bodyIndexMat.forEach<cv::Vec3b>([&](cv::Vec3b &p, const int* position) {
		int index = position[0] * depthWidth + position[1];
		depthData.push_back(depthBuffer[index]);
	});

	std::cout << "AVERAGE DISTANCE " << calculateAverage(depthData) << std::endl;
	*/

	int index = (depthHeight / 2) * depthWidth + (depthWidth / 2);
	// std::cout << "depthData " << depthData << std::endl;
	int distance = depthBuffer[index];
	distanceF = static_cast<float>(distance) / 1000.0;
	std::cout << "FRAME " << frameCount << " MIDDLE POINT DISTANCE IS " << distanceF << "m" << std::endl;
	frameCount++;

	/*if (distance == 0 && (distance < 500 || distance > 4500))
		std::cout << "OVERFLOW" << std::endl;*/
}


// Calculate the average inside a vector
// Not used in this version
int Kinect::calculateAverage(std::vector<int>& nums) {
	int sum = 0;
	for (std::vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter++) {
		sum += *iter;
	}
	return (sum / nums.size());
}


// Convert data structure from float to string
std::string Kinect::convert(float num) {
	std::ostringstream buffer;
	buffer << num;
	return buffer.str();
}
