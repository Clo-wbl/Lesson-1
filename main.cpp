/** LESSON 2 */
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    // Read file
    Mat im1 = imread("..\\..\\img\\IMG_4168.jpg");
    Mat im2 = imread("..\\..\\img\\IMG_4170.jpg");

    if (im1.empty())
    {
        cout << "First Image loading has failed" << endl;
        system("pause");
        return -1;
    }

    if (im1.empty())
    {
        cout << "Second Image loading has failed" << endl;
        system("pause");
        return -1;
    }

    Mat imConcat;
    hconcat(im1, im2, imConcat);

    // Display file
    namedWindow("Image Display", WINDOW_AUTOSIZE);
    imshow("Image Display", imConcat);

    waitKey(0); // wait for a key in the window

    // Find the feature points
    Ptr<AKAZE> akaze = AKAZE::create();
    vector<KeyPoint> keypoints;
    Mat descriptors;
    akaze->detectAndCompute(imConcat, noArray(), keypoints, descriptors);

    Mat imFeatPt;
    drawKeypoints(imConcat, keypoints, imFeatPt);

    imshow("Image avec keypoints", imFeatPt);
    waitKey(0);

    // // Gray scale
    // Mat grayImage;

    // cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // namedWindow("Gray Image", WINDOW_AUTOSIZE);
    // imshow("Gray Image", grayImage);
    // waitKey(0);

    // // Circle
    // Mat circleImage = image;

    // int listPointsX[5] {100,200,300,150,250};
    // int listPointsY[5] {100,100,100,150,150};
    // int radius = 45;
    // int listColorsR[5] {0,0,255,255,0};
    // int listColorsG[5] {0,0,0,255,255};
    // int listColorsB[5] {255,0,0,0,0};
    // int thickness = 4;
    // for(int i = 0; i < 5; i++){
    //     circle(circleImage, Point(listPointsX[i],listPointsY[i]), radius, Scalar(listColorsB[i], listColorsG[i], listColorsR[i]), thickness);
    // }
    // line(image, Point(55, 250), Point(345, 250), Scalar(255, 0, 255), thickness, LINE_4);
    // imshow("Circle and Line", circleImage);

    // waitKey(0); // wait for a key in the window

    // Destroy
    im1.release();
    im2.release();
    imConcat.release();

    return 0;
}