
#include <iostream>
#include <Kinect.h>
#include <Windows.h>

#include <opencv2/opencv.hpp>
#include <wrl/client.h>

#include "app.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	try {
		Kinect kinect;
		kinect.run();
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	return 0;
}