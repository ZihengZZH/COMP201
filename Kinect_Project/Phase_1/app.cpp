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
    // Main Loop
    while( true ){

        // Update Data
        update();

        // Draw Data
        draw();

        // Show Data
        show();

		// Get & print depth data
		getDepthData();

        // Key Check
        const int key = cv::waitKey( 10 );
        if( key == VK_ESCAPE ){
            break;
        }
    }
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

	// Initialize BodyIndex
	initializeBodyIndex();

	// Initialize Depth
	initializeDepth();


    // Wait a Few Seconds until begins to Retrieve Data from Sensor ( about 2000-[ms] )
    std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
}

// Initialize Sensor
inline void Kinect::initializeSensor()
{
    // Open Sensor
    ERROR_CHECK( GetDefaultKinectSensor( &kinect ) );

    ERROR_CHECK( kinect->Open() );

    // Check Open
    BOOLEAN isOpen = FALSE;
    ERROR_CHECK( kinect->get_IsOpen( &isOpen ) );
    if( !isOpen ){
        throw std::runtime_error( "failed IKinectSensor::get_IsOpen( &isOpen )" );
    }
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

// Initialize BodyIndex
inline void Kinect::initializeBodyIndex()
{
	// Open BodyIndex Reader
	ComPtr<IBodyIndexFrameSource> bodyIndexFrameSource;
	ERROR_CHECK(kinect->get_BodyIndexFrameSource(&bodyIndexFrameSource));
	ERROR_CHECK(bodyIndexFrameSource->OpenReader(&bodyIndexFrameReader));

	// Retrieve BodyIndex Description
	ComPtr<IFrameDescription> bodyIndexFrameDescription;
	ERROR_CHECK(bodyIndexFrameSource->get_FrameDescription(&bodyIndexFrameDescription));
	ERROR_CHECK(bodyIndexFrameDescription->get_Width(&bodyIndexWidth)); // 512
	ERROR_CHECK(bodyIndexFrameDescription->get_Height(&bodyIndexHeight)); // 424
	ERROR_CHECK(bodyIndexFrameDescription->get_BytesPerPixel(&bodyIndexBytesPerPixel)); // 1

	// Allocation BodyIndex Buffer
	bodyIndexBuffer.resize(bodyIndexWidth * bodyIndexHeight);

	// Color Table for Visualization
	colors[0] = cv::Vec3b(255, 0, 0); // Blue
	colors[1] = cv::Vec3b(0, 255, 0); // Green
	colors[2] = cv::Vec3b(0, 0, 255); // Red
	colors[3] = cv::Vec3b(255, 255, 0); // Cyan
	colors[4] = cv::Vec3b(255, 0, 255); // Magenta
	colors[5] = cv::Vec3b(0, 255, 255); // Yellow
}

// Initialize Depth
inline void Kinect::initializeDepth() {
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

	// Update BodyIndex
	updateBodyIndex();

	// Update Depth
	updateDepth();

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

// Update BodyIndex
inline void Kinect::updateBodyIndex()
{
	// Retrieve BodyIndex Frame
	ComPtr<IBodyIndexFrame> bodyIndexFrame;
	const HRESULT ret = bodyIndexFrameReader->AcquireLatestFrame(&bodyIndexFrame);
	if (FAILED(ret)) {
		return;
	}

	// Retrieve BodyIndex Data
	ERROR_CHECK(bodyIndexFrame->CopyFrameDataToArray(static_cast<UINT>(bodyIndexBuffer.size()), 
		&bodyIndexBuffer[0]));
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

// Draw Data
void Kinect::draw()
{
    // Draw Color
    drawColor();

	// Draw BodyIndex
	drawBodyIndex();

	// Draw Depth
	drawDepth();
}

// Draw Color
inline void Kinect::drawColor()
{
    // Create cv::Mat from Color Buffer
    colorMat = cv::Mat( colorHeight, colorWidth, CV_8UC4, &colorBuffer[0] );

}

// Draw BodyIndex
inline void Kinect::drawBodyIndex()
{

	// Visualization Color to Each Index
	bodyIndexMat = cv::Mat::zeros(bodyIndexHeight, bodyIndexWidth, CV_8UC3);
	bodyIndexMat.forEach<cv::Vec3b>([&](cv::Vec3b &p, const int* position) {
		uchar index = bodyIndexBuffer[position[0] * bodyIndexWidth + position[1]];
		if (index != 0xff) {
			p = colors[index];
		}
	});
	// Lambda expression to assign every bodyIndexBuffer element with color

}

// Draw Depth
inline void Kinect::drawDepth() {
	// Create cv::Mat from Depth Buffer
	depthMat = cv::Mat(depthHeight, depthWidth, CV_16UC1, &depthBuffer[0]);
}

// Show Data
void Kinect::show()
{
    // Show Color
    showColor();

	// Show BodyIndex
	showBodyIndex();

	// Show Depth
	showDepth();
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

	// Draw a point in the center of image to indicate where depth data is taken
	cv::Size s = resizeMat.size();
	int height = s.height;
	int width = s.width;
	cv::Point point = cv::Point(width / 2, height / 2);
	cv::circle(resizeMat, point, 7, cv::Scalar(153, 76, 0), -1);

	// Print the distance information in the image
	// Print it every ten frames
	cv::Point textPos = cv::Point(width - 600, height - 10);
	if (frameCount % 10 == 0) {
		text = "MIDDLE-POINT DISTANCE " + convert(distanceF) + "m";
		temp = text;
	}
	else {
		text = temp;
	}
	cv::putText(resizeMat, text, textPos, 2, 1.1, cv::Scalar(153, 76, 0), 1);

    // Show Image
    cv::imshow( "Color", resizeMat);
}

// Show BodyIndex
inline void Kinect::showBodyIndex()
{
	// Show Image
	cv::imshow("BodyIndex", bodyIndexMat);
}

// Show Depth
inline void Kinect::showDepth() {
	if (depthMat.empty()) {
		return;
	}

	// Scaling ( 0-8000 -> 255-0 )
	cv::Mat scaleMat;
	depthMat.convertTo(scaleMat, CV_8U, -255.0 / 8000.0, 255.0);
	//cv::applyColorMap( scaleMat, scaleMat, cv::COLORMAP_BONE );

	cv::Size s = scaleMat.size();
	int height = s.height;
	int width = s.width;
	//std::cout << "ROWS " << rows << "COLS " << cols << std::endl;
	//std::cout << "DEPTH HEIGHT " << depthHeight << "DEPTH WIDTH "<< depthWidth << std::endl;

	// scaleMat.at<cv::Vec3b>((rows/2), (cols/2)) = cv::Vec3b(255, 0, 255);
	cv::Point point = cv::Point(width / 2, height / 2);
	cv::circle(scaleMat, point, 5, cv::Scalar(0, 255, 255), -1);

	// Show Image
	cv::imshow("Depth", scaleMat);
}

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
