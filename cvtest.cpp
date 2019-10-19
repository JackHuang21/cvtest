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
#include <iostream>

using namespace cv;

int main(int argc, char* argv[])
{
	Mat img(2, 2, CV_8UC3, Scalar(0, 0, 255));
	std::cout << "img = " << std::endl;
	std::cout << img << std::endl;
	return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table)
{
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	uchar* p = NULL;
	for (int i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (int j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}

	return I;
}