/** LESSON 4 */
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <string>

using namespace std;
using namespace cv;

int argNum = 30;

int main(int argc, char **argv)
{

    // Open the video
    VideoCapture vid("..\\..\\img\\flog.m1V");
    if (!vid.isOpened())
    {
        std::cerr << "Error while opening the video" << std::endl;
        return -1;
    }

    // Read video frame by frame
    Mat frame;
    while (true)
    {
        vid >> frame; // Put one frame at a time
        if (frame.empty())
        {
            std::cout << "Video ended" << std::endl;
            break;
        }

        imshow("Video", frame); // Print frame
        if (waitKey(25) == 27)  // Each frame is displayed 25ms and escape if ESC key pressed
        {
            break;
        }
    }

    // Go back to the beginning of the video
    // vid.set(CAP_PROP_FORMAT, 0);

    // Read it a second time but displaying feature points too

    // Feature points
    vector<KeyPoint> keypoints;
    Mat imFeatPt;

    while (true)
    {
        vid >> frame; // Put one frame at a time
        if (frame.empty())
        {
            std::cout << "Video ended" << std::endl;
            break;
        }

        // ORB
        Ptr<FastFeatureDetector> fast = FastFeatureDetector ::create();
        fast->detect(frame, keypoints);

        drawKeypoints(frame, keypoints, imFeatPt);

        imshow("Video with keypoints", imFeatPt);
        if (waitKey(25) == 27) // Each frame is displayed 25ms and escape if ESC key pressed
        {
            break;
        }
    }

    // Destroy
    vid.release();
    frame.release();
    imFeatPt.release();

    return 0;
}