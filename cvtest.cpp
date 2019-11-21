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


int main(int argc, char* argv[])
{
	std::string imageName = "images/circle.png";
	Mat src = imread(samples::findFile(imageName), IMREAD_COLOR);
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	// median blur 
	medianBlur(dst, dst, 3);
	std::vector<Vec3f> circles;
	HoughCircles(dst, circles, HOUGH_GRADIENT, 1, dst.rows / 16, 100, 30, 1, 30);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		circle(src, center, 1, Scalar(0, 100, 100), 1, LINE_AA);
		int radius = c[2];
		circle(src, center, radius, Scalar(255, 0, 255), 1, LINE_AA);
	}
	imshow("dst", src);
	waitKey(0);
	return EXIT_SUCCESS;
}

