#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

static void help(char* progName)
{
    std::cout << std::endl;
    std::cout << "this program shows how to filter images with mask: " << std::endl;
    std::cout << "1. the write it yourself" << std::endl;
    std::cout << "2. filter2d way" << std::endl;
    std::cout << "usage:" << progName << " [image_path -- default lena.jpg] [G -- grayscale]" << std::endl;     
}

void Sharpen(const cv::Mat& img, cv::Mat& result);

int main(int argc, char* argv[])
{
    help(argv[0]);
    const char* filename = argc >= 2 ? argv[1] : "C:\\Users\\q9947\\Documents\\source\\repo\\cvtest\\images\\lena.jpg";
    cv::Mat src;
    cv::Mat dst0;
    cv::Mat dst1;

    if (argc >= 3 && !strcmp("G", argv[2]))
        src = cv::imread(cv::samples::findFile(filename), cv::IMREAD_GRAYSCALE);
    else
        src = cv::imread(cv::samples::findFile(filename), cv::IMREAD_COLOR);

    if (src.empty())
    {
        std::cerr << "can't open image [" << filename << "]" << std::endl;
        return EXIT_FAILURE;
    }

    cv::namedWindow("input", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("output", cv::WINDOW_AUTOSIZE);

    cv::imshow("input", src);
    double t = (double)cv::getTickCount();
    
    Sharpen(src, dst0);
    
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "hand write function time passed in seconds: " << t << std::endl;
    
    cv::imshow("output", dst0);
    cv::waitKey();
    cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0,
                                            -1, 5, -1,
                                            0, -1, 0);
    t = (double)cv::getTickCount();
    filter2D(src, dst1, src.depth(), kernel);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    std::cout << "built-in filter 2D time passed in seconds: " << t << std::endl;

    cv::imshow("output", dst1);
    cv::waitKey();

    return EXIT_SUCCESS;
}

void Sharpen(const cv::Mat& img, cv::Mat& result)
{
    CV_Assert(img.depth() == CV_8U);

    const int nChannels = img.channels();
    result.create(img.size(), img.type());

    for (int i = 1; i < img.rows - 1; i++)
    {
        const uchar* previous = img.ptr<uchar>(i - 1);  // 上一行数据
        const uchar* current = img.ptr<uchar>(i);       // 当前行数据
        const uchar* next = img.ptr<uchar>(i + 1);      // 下一行数据

        uchar* output = result.ptr<uchar>(i);

        for (int j = nChannels; j < nChannels * (img.cols - 1); j++)
        {
            *output++ = cv::saturate_cast<uchar>(5 * current[j] -
                current[j - nChannels] - current[j + nChannels] - previous[j] - next[j]);
        }
    }

    result.row(0).setTo(cv::Scalar(0));
    result.row(result.rows - 1).setTo(cv::Scalar(0));
    result.col(0).setTo(cv::Scalar(0));
    result.col(result.cols - 1).setTo(cv::Scalar(0));
}
