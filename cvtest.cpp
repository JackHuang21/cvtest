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


int	main(int argc, char* argv[])
{
	std::string imgName = "images/lena.jpg";
	std::cout << "\t remap demo" << std::endl;
	std::cout << "1. reduce the image to half size and will display it in the middle..." << std::endl;
	std::cout << "2. turn the image upside down..." << std::endl;
	std::cout << "3. reflect the iamge left to right..." << std::endl;
	std::cout << "4. cobination 2 & 3..." << std::endl;

	Mat src = imread(imgName, IMREAD_COLOR);
	if (src.empty())
	{
		std::cout << "can't load the image..." << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<Mat> bgrPlanes;
	split(src, bgrPlanes);
	
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = range;
	bool uniform = true;
	bool accumulate = false;
	Mat bHist, gHist, rHist;
	calcHist(&bgrPlanes[0], 1, 0, Mat(), bHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgrPlanes[1], 1, 0, Mat(), gHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgrPlanes[2], 1, 0, Mat(), rHist, 1, &histSize, &histRange, uniform, accumulate);
	
	int histW = 512;
	int histH = 512;
	int binW = cvRound((double)histW / histSize);
	Mat histImage(histW, histH, CV_8UC3, Scalar(0, 0, 0));

	normalize(bHist, bHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(gHist, gHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(rHist, rHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(binW * (i - 1), histH - cvRound(bHist.at<float>(i - 1))), 
			Point(binW * i, histH - cvRound(bHist.at<float>(i))), Scalar(255, 0, 0));
		line(histImage, Point(binW * (i - 1), histH - cvRound(gHist.at<float>(i - 1))),
			Point(binW * i, histH - cvRound(gHist.at<float>(i))), Scalar(0, 255, 0));
		line(histImage, Point(binW * (i - 1), histH - cvRound(rHist.at<float>(i - 1))),
			Point(binW * i, histH - cvRound(rHist.at<float>(i))), Scalar(0, 0, 255));
	}


	imshow("src", src);
	imshow("hist", histImage);
	waitKey(0);
	return EXIT_SUCCESS;
}

