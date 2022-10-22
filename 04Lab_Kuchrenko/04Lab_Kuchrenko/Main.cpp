#include <iostream>
#include <opencv2/opencv.hpp>
#include "SobelOperator.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("C:/dev/MMOZ/Tif/Geneva.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat sobel_image(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat sobel_lib_image(image.rows, image.cols, CV_8UC1, Scalar(0));

	sobel_operator(image, sobel_image);
	Sobel(image, sobel_lib_image, -1, 1, 1);
	imshow("Original image", image);
	imshow("Sobel-filtered image", sobel_image);
	imshow("Sobel-lib-filtered image", sobel_lib_image);
	waitKey(0);
	return 0;
}
