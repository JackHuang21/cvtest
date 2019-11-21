/**
 * @file		cvtest.cpp
 * @brief		A project for opencv test.
 * @details		
 * 
 * @author		Jack
 * @version		V0.1
 * @date		2019-10-16
 * @history		
 */
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;

const int maxValueH = 180;
const int maxValue = 255;
const std::string captureWindowName = "Video Capture";
const std::string detectionWindowName = "Object Detection";
int lowH = 0;
int lowS = 0;
int lowV = 0;
int highH = maxValueH;
int highS = maxValue;
int highV = maxValue;

static void onLowHThreshTrackbar(int, void*)
{
	lowH = min(highH - 1, lowH);
	setTrackbarPos("Low H", detectionWindowName, lowH);
}

static void onHighHThreshTrackbar(int, void*)
{
	highH = min(highH, lowH + 1);
	setTrackbarPos("High H", detectionWindowName, highH);
}

static void onLowSThreshTrackbar(int, void*)
{
	lowS = min(highS - 1, lowS);
	setTrackbarPos("Low S", detectionWindowName, lowS);
}

static void onHighSThreshTrackbar(int, void*)
{
	highS = min(highS, lowS + 1);
	setTrackbarPos("High S", detectionWindowName, highS);
}

static void onLowVThreshTrackbar(int, void*)
{
	lowV = min(highV - 1, lowV);
	setTrackbarPos("Low V", detectionWindowName, lowV);
}

static void onHighVThreshTrackBar(int, void*)
{
	highV = min(highV, lowV + 1);
	setTrackbarPos("High V", detectionWindowName, highV);
}


int main(int argc, char* argv[])
{
	VideoCapture cap;
	cap.open(1);
	if (!cap.isOpened())
	{
		std::cout << "can't open the camera..." << std::endl;
		return EXIT_FAILURE;
	}

	namedWindow(captureWindowName);
	namedWindow(detectionWindowName);

	createTrackbar("Low H", detectionWindowName, &lowH, maxValueH, onLowHThreshTrackbar);
	createTrackbar("High H", detectionWindowName, &highH, maxValueH, onHighHThreshTrackbar);
	createTrackbar("Low S", detectionWindowName, &lowS, maxValue, onLowSThreshTrackbar);
	createTrackbar("High S", detectionWindowName, &highS, maxValue, onHighSThreshTrackbar);
	createTrackbar("Low V", detectionWindowName, &lowV, maxValue, onLowVThreshTrackbar);
	createTrackbar("High V", detectionWindowName, &highV, maxValue, onHighVThreshTrackBar);

	Mat frame;
	Mat frameHSV;
	Mat frameThreshhold;

	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		cvtColor(frame, frameHSV, COLOR_BGR2HSV);
		inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameThreshhold);
		imshow(captureWindowName, frame);
		imshow(detectionWindowName, frameThreshhold);
		char key = (char)waitKey(30);
		if (key == 'q') break;
	}

	waitKey(0);
	return EXIT_SUCCESS;
}

