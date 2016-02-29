#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// Name of the image to load
	char ImageName[] = "../../0_SampleImages/img.jpg";
	Mat image, result;

	// Load image and check it is correct
	image = cv::imread(ImageName);
	if (!image.data) {
		cout << "Error at loading image" << ImageName << endl;
		exit(1);
	}

	// Create look-up table: 1 row, 256 cols and 8 bits
	Mat lut(1, 256, CV_8U);

	// Perform the transformation in the look-up table
	for (int i = 0; i < 256; i++) {
		// Invert
		lut.at<uchar>(i) = 255 - i; 
		// Square root (up shadows especially)
		//lut.at<uchar>(i) = pow((float) i * 255, (float)(1 / 2.0)); 
		// Cubic (up highlights especially)
		//lut.at<uchar>(i) = pow((float) i, (float) 3.0) / (255 * 255); 
	}

	// Apply the transformation to the image
	LUT(image, lut, result);

	// Show image
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", image);

	// Show result
	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	imshow("Result", result);

	// Wait for a key to be pressed
	waitKey(0);

	return 0;
}