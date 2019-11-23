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

	Point2f srcTri[3];
	srcTri[0] = Point2f(0.f, 0.f);
	srcTri[1] = Point2f(src.cols - 1.f, 0.f);
	srcTri[2] = Point2f(0.f, src.rows - 1.f);

	Point2f dstTri[3];
	dstTri[0] = Point2f(0.f, src.rows * 0.33f);
	dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
	dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);

	Mat warpMat = getAffineTransform(srcTri, dstTri);
	Mat dst = Mat::zeros(src.rows, src.cols, src.type());
	warpAffine(src, dst, warpMat, dst.size());
	
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = -50.0;
	double scale = 1;

	Mat rotMat = getRotationMatrix2D(center, angle, scale);
	Mat rotDst;
	warpAffine(dst, rotDst, rotMat, dst.size());

	imshow("src", src);
	imshow("warp", dst);
	imshow("warp and rotate", rotDst);
	waitKey(0);
	return EXIT_SUCCESS;
}

