#include <iostream>
#include <opencv2/opencv.hpp>
#include "CannyOperator.h"
#include "SobelOperator.h"

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
	Mat sobel_image(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat canny_lib_image(image.rows, image.cols, CV_8UC1, Scalar(0));

	canny_operator(image, canny_image, 20, 90);
	sobel_operator(image, sobel_image);
	//Canny(image, canny_lib_image, 70, 210);
	imshow("Original image", image);
	imshow("Sobel image", sobel_image);
	imshow("Canny-filtered image", canny_image);
	//imshow("Canny-lib-filtered image", canny_lib_image);
	waitKey(0);
	return 0;
}
