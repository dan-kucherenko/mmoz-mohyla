#include <iostream>
#include <opencv2/opencv.hpp>
#include "OptimalThreshold.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("C:/dev/MMOZ/Tif/IM11.tif");
	//string imageName("C:/dev/MMOZ/Tif/contour.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat optimal_thresholded(image.rows, image.cols, CV_8UC1, Scalar(0));
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat histogram;
	optimal_threshold(image, optimal_thresholded);
	imshow("Input image", image);
	imshow("Image after optimal thresholding", optimal_thresholded);
	//imshow("Output image histogram", histogram);
	waitKey(0);
	return 0;
}