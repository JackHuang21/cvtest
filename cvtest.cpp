#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout << "-----------------------------------------------" << endl;
    cout << "This program shows how to create matrices(cv::Mat)";
    cout << " in OpenCVand its serial";
    cout << " out capabilities." << endl;
    cout << "That is, cv::Mat M(...); M.create and cout << M. " << endl;
    cout << "Shows how output can be formatted to OpenCV, python, numpy," << endl;
    cout << " csv and C styles." << endl;
    cout << "Usage:" << endl;
    cout << "./mat_the_basic_image_container" << endl;
    cout << "-----------------------------------------------" << endl;
}


int main(int, char**)
{
    help();

    // create by using constructor
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << M << endl << endl;

    // create by using the create function
    M.create(4, 4, CV_8UC(2));
    cout << "M = " << endl << M << endl;

    // create multidimensional matrices
    int sz[3] = { 2, 2, 3 };
    Mat L(3, sz, CV_8UC1(1), Scalar::all(0));

    // create using matlab style eye, ones, zero matrix
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << E << endl;
    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << O << endl;
    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    cout << "Z = " << endl << Z << endl;

    // create a 3x3 double-precision identity matrix 
    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << C << endl;
    
    // do the same with initializer_list
#ifdef CV_CXX11
    C = (Mat_<double>({ 0, -1, 0, -1, 5, -1, 0, -1, 0 })).reshape(3);
    cout << "C = " << endl << C << endl;
#endif

    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << RowClone << endl;

    // fill a matrix with random values
    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));

    // Demonstrate the output formating options
    cout << "R (default)" << endl << R << endl;
    cout << "R (python)" << endl << format(R, Formatter::FMT_PYTHON) << endl;
    cout << "R (numpy)" << endl << format(R, Formatter::FMT_NUMPY) << endl;
    cout << "R (csv)" << endl << format(R, Formatter::FMT_CSV) << endl;
    cout << "R (c)" << endl << format(R, Formatter::FMT_C) << endl;

    Point2f P(5, 1);
    cout << "Point (2D) = " << P << endl;
    
    Point3f P3f(2, 6, 7);
    cout << "Point (3D) = " << P3f << endl;

    vector<float> v;
    v.push_back((float)CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    cout << "Vector of floats via Mat = " << Mat(v) << endl;

    return 0;
}





