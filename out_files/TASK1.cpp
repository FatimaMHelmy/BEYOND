
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/*
void swap_faces(Mat& image, Rect& face1, Rect& face2) {
    // Check if the faces are within the image boundaries
    if (face1.x >= 0 && face1.y >= 0 && face1.x + face1.width <= image.cols && face1.y + face1.height <= image.rows &&
        face2.x >= 0 && face2.y >= 0 && face2.x + face2.width <= image.cols && face2.y + face2.height <= image.rows) {

        // Calculate the difference in width and height between the faces
        int widthDiff = face2.width - face1.width;
        int heightDiff = face2.height - face1.height;

        // Adjust the ROI of face2 to match the size of face1
        Rect adjustedFace2(face2.x + widthDiff, face2.y + heightDiff, face1.width, face1.height);

        // Check if the adjusted faces have the same size
        if (adjustedFace2.width == face1.width && adjustedFace2.height == face1.height) {
            // Extract the regions of interest (ROI) for the faces
            Mat roi1 = image(face1);
            Mat roi2 = image(adjustedFace2);

            // Copy the pixels from face1 to face2
            roi1.copyTo(roi2);

            // Copy the adjusted ROI back to the original position of face2
            roi2.copyTo(image(adjustedFace2));
        }
    }
}
*/

void swap_faces(Mat& image, Rect& face1, Rect& face2) {
    // Check if the faces are within the image boundaries
    if (face1.x >= 0 && face1.y >= 0 && face1.x + face1.width <= image.cols && face1.y + face1.height <= image.rows &&
        face2.x >= 0 && face2.y >= 0 && face2.x + face2.width <= image.cols && face2.y + face2.height <= image.rows) {

        // Compute the intersection of the face regions
        Rect intersection = face1 & face2;

        // Check if there is a valid intersection
        if (intersection.width > 0 && intersection.height > 0) {
            // Get the face regions
            Mat temp1 = image(face1);
            Mat temp2 = image(face2);

            // Get the intersection region
            Mat intersectionRegion = image(intersection);

            // Copy the pixels from face2 to face1's intersection region
            temp2(intersection - face2.tl()).copyTo(intersectionRegion);

            // Copy the pixels from face1 to face2's intersection region
            temp1(intersection - face1.tl()).copyTo(image(face2));
        }
    }
}


/*

void swap_faces(Mat& image, Rect& face1, Rect& face2) {
    // Check if the faces are within the image boundaries
    if (face1.x >= 0 && face1.y >= 0 && face1.x + face1.width <= image.cols && face1.y + face1.height <= image.rows &&
        face2.x >= 0 && face2.y >= 0 && face2.x + face2.width <= image.cols && face2.y + face2.height <= image.rows) {

        // Get the face regions
        Mat temp1 = image(face1);
        Mat temp2 = image(face2);

        // Resize the face regions to the same size
        Size maxSize(face1.width, face1.height);
        resize(temp2, temp2, maxSize);

        // Replace the pixels of face1 with the pixels of face2
        temp2.copyTo(image(face1));

        // Resize the face regions to the same size
        Size maxSize2(face2.width, face2.height);
        resize(temp1, temp1, maxSize2);

        // Replace the pixels of face2 with the pixels of face1
        temp1.copyTo(image(face2));
    }
}*/


void detect_faces(const string& imagePath, const string& cascadePath) {
    // Read the image from its path and check if it is loaded successfully
    Mat img = imread(imagePath);
    if (img.empty()) {
        cout << "Failed to load image: " << imagePath << endl;
        return;
    }

    // Load faceCascade XML file and check that it is loaded successfully
    CascadeClassifier faceCascade;
    faceCascade.load(cascadePath);
    if (faceCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return;
    }

    // Detect faces in the image
    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    // Check if there are at least two faces detected
    if (faces.size() < 2) {
        cout << "Not enough faces detected in the image." << endl;
        return;
    }

    // Swap the faces of adjacent persons
    for (size_t i = 0; i < faces.size() - 1; i++) {
        Rect currentFace = faces[i];
        Rect nextFace = faces[i + 1];

        // Swap the faces by swapping the image regions
        swap_faces(img, currentFace, nextFace);
    }

    // Draw circles around the detected faces
    for (const Rect& face : faces) {
        Point center(face.x + face.width / 2, face.y + face.height / 2);
        int radius = max(face.width, face.height) / 2;
        circle(img, center, radius, Scalar(255, 0, 255), 3);
    }

    // Create a window and display the image with detected faces
    namedWindow("Detected Faces", WINDOW_NORMAL);
    imshow("Detected Faces", img);
    waitKey(0);
    destroyWindow("Detected Faces");
}

int main() {
    string imgPath;
    string cascadePath = "./haarcascade_frontalface_default.xml";

    cout << "Enter the path to the image: ";
    cin >> imgPath;

    detect_faces(imgPath, cascadePath);

    return 0;
}


//////////////////////////////


