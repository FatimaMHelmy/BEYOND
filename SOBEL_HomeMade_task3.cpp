
#include <iostream>
#include <opencv2/opencv.hpp>

class SobelEdgeDetector {
private:
    cv::Mat image;                   // original_image
    cv::Mat edge_image;             // image after applaying both vertical and horizontal sobel
    cv::Mat edge_image_horizontal; // image after applaying both  horizontal sobel
    cv::Mat edge_image_vertical;  // image after applaying both vertical  sobel
    cv::Mat smoothed;            // it's optional part to have more smoothed image 


    cv::Mat vertical_sobelfilter;    // vertical filter matrix 
    cv::Mat horizontal_sobel_filter;// horizontal filter matrix 


public:

    SobelEdgeDetector(const std::string& path) {

        // read the img and check that it is loaded successfully  if not run a stored img 
        image = cv::imread(path, cv::IMREAD_GRAYSCALE);
        if (image.empty()) {
            std::cout << "Failed to load image." << std::endl;
            image = cv::imread("./test.png", cv::IMREAD_GRAYSCALE);
            //return;
        }

        // intialize the sobel filter manually
        vertical_sobelfilter = (cv::Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
        horizontal_sobel_filter = (cv::Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);;

        // call method wich apply filter in the original img by making the convolution 
        detectEdges();
    }

    /* this method for making the img more smooth to avoid the noise it would be more efficient if 
    u use track bar to control gaussian filter intensity */

    cv::Mat img_smoothing_fn() {

        cv::Mat blurred_image;
        cv::Mat sharpened_image;
        cv::GaussianBlur(image, blurred_image, cv::Size(15, 15), 0, 0, cv::BORDER_DEFAULT);
        sharpened_image = image + (image - blurred_image);
        return blurred_image;
    }

    // this method for applying the hand made sobel filter ':) 

    void detectEdges() {

        // optional part if you wanna make the image more smoothed by applying gaussian or sharping 
        smoothed = cv::Mat::zeros(image.size(), CV_8U);
        smoothed = img_smoothing_fn();

        // intialization for output filtered images 
        cv::Mat magnitude = cv::Mat::zeros(image.size(), CV_32F);
        edge_image = cv::Mat::zeros(image.size(), CV_8U);
        edge_image_horizontal = cv::Mat::zeros(image.size(), CV_8U);
        edge_image_vertical = cv::Mat::zeros(image.size(), CV_8U);
        

        /* 
                                !!!!!!!!! BE CAREFUL
         WE WILL START FROM SECOND COLUMN AND ROW By starting from the second row and column,
         you avoid accessing pixels outside the image boundaries, 
         U CAN USING PADDINF INSTEAD OF THAT 
        
        */

        for (int i = 1; i < smoothed.rows-1 ; i++) {
            for (int j = 1; j < smoothed.cols-1 ; j++) {
                float sum_ver = 0.0f;
                float sum_hor = 0.0f;

                // Convolve the image region with the Sobel operators
                for (int m = -1; m <= 1; m++) {
                    for (int n = -1; n <= 1; n++) {
                        sum_ver += smoothed.at<uchar>(i + m, j + n) * vertical_sobelfilter.at<float>(m + 1, n + 1);
                        sum_hor += smoothed.at<uchar>(i + m, j + n) * horizontal_sobel_filter.at<float>(m + 1, n + 1);
                    }
                }

                // the gradients which  represent the changes in pixel intensity in the horizontal and vertical directions.
                float magnitude_value = std::sqrt(sum_ver * sum_ver + sum_hor * sum_hor);

                // STORE VALUES IN THE FILTERD IMAGE 
                edge_image.at<uchar>(i, j) = static_cast<uchar>(magnitude_value);
                edge_image_horizontal.at<uchar>(i, j) = static_cast<uchar>(sum_hor);
                edge_image_vertical.at<uchar>(i, j) = static_cast<uchar>(sum_ver);

            }
        }

    }

    void showEdgeImage() {

                // display the four images in one window 
        cv::namedWindow("original vs filterd image", cv::WINDOW_NORMAL);

        cv::Mat combined_image_1;
        cv::Mat combined_image_2;
        cv::Mat the_grid;

        cv::hconcat(smoothed, edge_image, combined_image_1);
        cv::hconcat(edge_image_vertical, edge_image_horizontal,combined_image_2);
        cv::vconcat(combined_image_1, combined_image_2, the_grid);

       
        cv::imshow("original vs filterd image", the_grid);

        cv::waitKey(0);
        cv::destroyWindow("original vs totaly_filtered vs vertical vs horizontal");
    }
};

int main() {
    // ask the user to enter the image path 
    std::string img_path;
    std::cout << "Enter the path to the image: ";
    std::cin >> img_path;

    // creat an instance from SobelEdgeDetector class 
    SobelEdgeDetector edge_detector(img_path);
    edge_detector.showEdgeImage();

    return 0;
}
