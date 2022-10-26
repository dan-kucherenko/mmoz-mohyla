#include <iostream>
#include <opencv2/opencv.hpp>
#include "CannyOperator.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("D:/dev/MMOZ/Tif/Geneva.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat canny_image(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat canny_lib_image(image.rows, image.cols, CV_8UC1, Scalar(0));

	canny_operator(image, canny_image, 60, 150);
	Canny(image, canny_lib_image, 60, 150);
	imshow("Original image", image);
	imshow("Canny-filtered image", canny_image);
	imshow("Canny-lib-filtered image", canny_lib_image);
	waitKey(0);
	return 0;
}
