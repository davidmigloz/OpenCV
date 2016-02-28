#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// Name of the image to load
	char ImageName[] = "../../0_SampleImages/img.jpg";
	Mat image;
	int row, col;

	// Load image and check it is correct
	image = cv::imread(ImageName);
	if (!image.data) {
		cout << "Error at loading image" << ImageName << endl;
		exit(1);
	}

	for (row = image.rows / 4; row < 3 * image.rows / 4; ++row) {
		for (col = image.cols / 4; col < 3 * image.cols / 4; ++col) {
			// Replace by black pixel
			image.at<Vec3b>(Point(col, row)) = Vec3b(0, 0, 0);
		}
	}

	// Show image
	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	imshow("Result", image);

	// Save result
	imwrite("Result.jpg", image);

	// Wait for a key to be pressed
	waitKey(0);

	return 0;
}