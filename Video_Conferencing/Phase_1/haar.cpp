#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>
#include <stdio.h>

// Function Headers
void detectAndDisplay(cv::Mat frame);

// Global variables
std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
std::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
std::string window_name = "Capture - Face detection";
cv::RNG rng(12345);


int main(int argr, const char** argv) {
	cv::VideoCapture capture(0);
	cv::Mat frame;

	// Eliminate for higher speed
	//capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	// 1. Load the cascades
	if (!face_cascade.load(face_cascade_name))
		std::cout << "--- ERROR LOADING ---\n";
	if (!eyes_cascade.load(eyes_cascade_name))
		std::cout << "--- ERROR LOADING ---\n";

	// 2. Read the video stream
	if (capture.isOpened()){
		while (true) {

			// 3. Apply the classifier to the frame
			capture.read(frame);
			if (!frame.empty()) {
				detectAndDisplay(frame);
			}
			else {
				std::cout << "--- NO CAPTURED FRAME ---\n";
				break;
			}
			int c = cv::waitKey(10);
			if ((char)c == 'c') break;
		}
	}

	return 0;
}


void detectAndDisplay(cv::Mat frame) {
	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30,30));

	for (size_t i = 0; i < faces.size(); i++) {
		cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		cv::ellipse(frame, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
		
		cv::Mat faceROI = frame_gray(faces[i]);
		std::vector<cv::Rect> eyes;

		// In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++) {
			cv::Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound(eyes[j].width + eyes[j].height*0.25);
			cv::circle(frame, center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		}
	}

	// Show the image
	imshow(window_name, frame);
}