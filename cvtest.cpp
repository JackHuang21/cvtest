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

static void updateMap(int& ind, Mat& mapX, Mat& mapY);


int	main(int argc, char* argv[])
{
	std::string imgName = "images/lena.jpg";
	std::string winName = "remap demo";
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
	Mat dst(src.size(), src.type());
	Mat mapX(src.size(), CV_32FC1);
	Mat mapY(src.size(), CV_32FC1);
	
	namedWindow(winName, WINDOW_AUTOSIZE);
	int ind = 0;
	while (1)
	{
		updateMap(ind, mapX, mapY);
		remap(src, dst, mapX, mapY, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow(winName, dst);
		char c = waitKey(1000);
		if (c == 27) break;
	}
	waitKey(0);
	return EXIT_SUCCESS;
}

void updateMap(int& ind, Mat& mapX, Mat& mapY)
{
	for (int i = 0; i < mapX.rows; i++)
	{
		for (int j = 0; j < mapX.cols; j++)
		{
			switch (ind)
			{
			case 0:
				if (j > mapX.cols * 0.25 && j < mapX.cols * 0.75 &&
					i > mapX.rows * 0.25 && i < mapX.rows * 0.75)
				{
					mapX.at<float>(i, j) = 2 * (j - mapX.cols * 0.25) + 0.5f;
					mapY.at<float>(i, j) = 2 * (i - mapX.cols * 0.25) + 0.5f;
				}
				else
				{
					mapX.at<float>(i, j) = 0;
					mapY.at<float>(i, j) = 0;
				}
				break;
			case 1:
				mapX.at<float>(i, j) = (float)j;
				mapY.at<float>(i, j) = (float)(mapX.rows - i);
				break;
			case 2:
				mapX.at<float>(i, j) = (float)(mapX.cols - j);
				mapY.at<float>(i, j) = (float)i;
				break;
			case 3:
				mapX.at<float>(i, j) = (float)(mapX.cols - j);
				mapY.at<float>(i, j) = (float)(mapX.rows - i);
				break;
			default:
				break;
			}
		}
	}
	// ind = (ind + 1) % 4;
}
