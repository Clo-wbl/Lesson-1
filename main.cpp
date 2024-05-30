#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    // Load Images
    vector<Mat> imgs;
    imgs.push_back(imread("..\\..\\img\\photometric\\cat.2.png", IMREAD_COLOR));
    imgs.push_back(imread("..\\..\\img\\photometric\\cat.4.png", IMREAD_COLOR));
    imgs.push_back(imread("..\\..\\img\\photometric\\cat.9.png", IMREAD_COLOR));
    Mat mask = imread("..\\..\\img\\photometric\\cat.mask.png", IMREAD_GRAYSCALE);

    // Check if images are loaded
    for (const auto& img : imgs) {
        if (img.empty()) {
            cout << "Image loading has failed" << endl;
            return -1;
        }
    }

    if (mask.empty()) {
        cout << "Mask loading has failed" << endl;
        return -1;
    }

    // --------- Get intensities ----------- //
    // Convert to gray scale
    vector<Mat> grayImgs;
    for (const auto& img : imgs) {
        Mat grayImg;
        cvtColor(img, grayImg, COLOR_BGR2GRAY);
        grayImgs.push_back(grayImg);
    }

    cout << "Img value at (250, 100): after gray scale before mask" << (int)grayImgs[0].at<uint8_t>(250, 100) << endl;

    // Apply mask to each grayscale image
    for (size_t i = 0; i < grayImgs.size(); ++i) {
        Mat masked;
        bitwise_and(grayImgs[i], grayImgs[i], masked, mask);
        grayImgs[i] = masked;

        // Print intensity value at (250, 100) before and after applying the mask
        cout << "Intensity value at (250, 100) in gray Image " << i + 1 << " before masking: " << (int)grayImgs[i].at<uint8_t>(250, 100) << endl;
        cout << "Intensity value at (250, 100) in masked gray Image " << i + 1 << ": " << (int)masked.at<uint8_t>(250, 100) << endl;
    }

    // Optional: Convert vector to array if needed
    vector<Mat> imgArray(grayImgs.begin(), grayImgs.end());

    // Destroy
    for (auto& img : grayImgs) {
        img.release();
    }
    mask.release();

    return 0;
}
