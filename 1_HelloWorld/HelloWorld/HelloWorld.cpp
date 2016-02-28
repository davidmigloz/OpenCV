#include <cstdio>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	// Name of the image to load
	char ImageName[] = "../../0_SampleImages/img.jpg";
	Mat image;

	// Load image and check it is correct
	image = cv::imread(ImageName);
	if (!image.data) {
		cout << "Error at loading image" << ImageName << endl;
		exit(1);
	}

	// Show image
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", image);

	// Wait for a key to be pressed
	waitKey(0);

	return 0;
}