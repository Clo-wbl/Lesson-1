#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
    // Load Images
    Mat img1 = imread("..\\..\\img\\photometric\\cat.2.png", IMREAD_COLOR);
    Mat img2 = imread("..\\..\\img\\photometric\\cat.4.png", IMREAD_COLOR);
    Mat img3 = imread("..\\..\\img\\photometric\\cat.9.png", IMREAD_COLOR);
    Mat mask = imread("..\\..\\img\\photometric\\cat.mask.png", IMREAD_COLOR);

    if (img1.empty() || img2.empty() || img3.empty() || mask.empty())
    {
        cout << "Image loading has failed" << endl;
        system("pause");
        return -1;
    }

    // --------- Get intensities ----------- //
    // Convert to gray scale
    Mat grayImg1, grayImg2, grayImg3, grayMask;
    cvtColor(img1, grayImg1, COLOR_BGR2GRAY);
    cvtColor(img2, grayImg2, COLOR_BGR2GRAY);
    cvtColor(img3, grayImg3, COLOR_BGR2GRAY);

    // Convert to float
    Mat fGrayImg1, fGrayImg2, fGrayImg3, fMask;
    grayImg1.convertTo(fGrayImg1, CV_32F);
    grayImg2.convertTo(fGrayImg2, CV_32F);
    grayImg3.convertTo(fGrayImg3, CV_32F);
    mask.convertTo(fMask, CV_32F, 1.0 / 255.0); // and normalize the mask between 0 and 1

    // Applying the mask
    filter2D(fGrayImg1, fGrayImg1, fGrayImg1.depth(), fMask);
    filter2D(fGrayImg2, fGrayImg2, fGrayImg2.depth(), fMask);
    filter2D(fGrayImg3, fGrayImg3, fGrayImg3.depth(), fMask);

    // Print some intensity values for verification
    cout << "Intensity value at (100, 100) in Image 1: " << fGrayImg1.at<float>(100, 100) << endl;
    cout << "Intensity value at (100, 100) in Image 2: " << fGrayImg2.at<float>(100, 100) << endl;
    cout << "Intensity value at (100, 100) in Image 3: " << fGrayImg3.at<float>(100, 100) << endl;

    // Destroy
    img1.release();
    grayImg1.release();
    fGrayImg1.release();
    img2.release();
    grayImg2.release();
    fGrayImg2.release();
    img3.release();
    grayImg3.release();
    fGrayImg3.release();
    mask.release();
    fMask.release();

    return 0;
}