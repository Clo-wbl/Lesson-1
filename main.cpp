#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main() {
    srand (time(NULL));
    // Load Images
    Mat img1 = imread("..\\..\\img\\not_same_plane\\img1.JPG", IMREAD_COLOR);
    Mat img2 = imread("..\\..\\img\\not_same_plane\\img2.JPG", IMREAD_COLOR);

    if (img1.empty() || img2.empty()) {
        cerr << "Error : impossible to load image." << endl;
        return 1;
    }

    // Ask number of points
    int numPoints;
    cout << "How many points do you want to extract ?\nAnswer : ";
    cin >> numPoints;

    int choose_algo;
    cout << "What algorithm do you want to use ?\n[1] ORB\n[2] AKAZE\nAnswer : ";
    cin >> choose_algo;

    // Extract features points
    Ptr<ORB> orb;
    Ptr<AKAZE> akaze;
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    switch(choose_algo){
        case 1 :
            orb = ORB::create(numPoints);
            orb->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            orb->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
            break;
        case 2 :
            akaze = AKAZE::create();
            akaze->setMaxPoints(numPoints);
            akaze->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
            akaze->detectAndCompute(img2, noArray(), keypoints2, descriptors2);
            break;
        default :
            cerr << "Error : algorithm doesn't exist." << endl;
            return 1;
    }

    // Create a BFMatcher object with Hamming's distance
    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);
    sort(matches.begin(), matches.end());

    // Filtering matches by distance
    float maxDistance = 100.0;
    cout << "Choose the threshold you want for your points (around 50 and 100 for a image 1200x2000)\nAnswer : ";
    cin >> maxDistance;
    vector<DMatch> filteredMatches;
    for (const DMatch& match : matches) {
        if (match.distance < maxDistance) {
            filteredMatches.push_back(match);
        }
    }
    cout << "Number of points remaining : " << filteredMatches.size() << endl;

    // Write features points in the file
    ofstream outFile("..\\..\\img\\not_same_plane\\extra_points\\extra_points.txt");
    for (const DMatch& match : filteredMatches) {
        Point2f pt1 = keypoints1[match.queryIdx].pt;
        Point2f pt2 = keypoints2[match.trainIdx].pt;
        Scalar color = Scalar(rand() % 256, rand() % 256, rand() % 256); // Random Color
        stringstream colorHex;
        colorHex << hex << setfill('0') << setw(2) << static_cast<int>(color[2])
                 << setw(2) << static_cast<int>(color[1]) << setw(2) << static_cast<int>(color[0]);
        outFile << "img1[ " << (int)(pt1.x + 0.5) << " ; " << (int)(pt1.y + 0.5) << " ]/img2[ " << (int)(pt2.x + 0.5) << " ; " << (int)(pt2.y + 0.5) << " ]/";
        outFile << colorHex.str() << "/";
        outFile << endl;

        // Draw circle of associated features points
        circle(img1, pt1, 30, color, 5);
        circle(img2, pt2, 30, color, 5);
    }
    outFile.close();

    // Save images with highlighted points
    imwrite("..\\..\\img\\not_same_plane\\extra_points\\img1_extra_points.jpg", img1);
    imwrite("..\\..\\img\\not_same_plane\\extra_points\\img2_extra_points.jpg", img2);

    return 0;
}