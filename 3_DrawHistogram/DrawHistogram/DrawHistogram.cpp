#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main() {
	// Name of the image to load
	char ImageName[] = "../../0_SampleImages/img.jpg";
	Mat src, dst;

	// Load image and check it is correct
	src = cv::imread(ImageName);
	if (!src.data) {
		cout << "Error at loading image" << ImageName << endl;
		exit(1);
	}

	// Split the image in three sub-images (BGR)
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	// Variables
	int histSize = 256; // Greay scale
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;

	// Where the histogram will be stored 
	Mat b_hist, g_hist, r_hist;

	// Calculate histogram
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Configure histogram
	int hist_width = 512;
	int hist_height = 400;
	int bin_width = cvRound((double)hist_width / histSize);
	Mat histImage(hist_height, hist_width, CV_8UC3, Scalar(0, 0, 0));

	// Normalize result [0, histImage.rows]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// Draw histogram for each channel
	for (int i = 1; i < histSize; i++) {
		line(histImage,
			Point(bin_width * (i - 1), hist_height - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_width * (i), hist_height - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage,
			Point(bin_width * (i - 1), hist_height - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_width * (i), hist_height - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage,
			Point(bin_width * (i - 1), hist_height - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_width * (i), hist_height - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	// Show image
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);

	// Show histogram
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Histogram", histImage);

	// Wait for a key to be pressed
	waitKey(0);

	return 0;
}