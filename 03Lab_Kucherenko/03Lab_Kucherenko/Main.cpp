#include <iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "Convolution.h"
#include "GaussianBlur.h"

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
	Mat convolusion_out(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat gaussian_out(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat gaussian_out_lib(image.rows, image.cols, CV_8UC1, Scalar(0));
	double mask[9] = { 1,1,1,
					  1,4,1,
					  1,1,1 };
	double k = 1.0 / 13.0;
	convolution(image, mask, 3, k, convolusion_out);
	gaussian_blur(image, gaussian_out, 5, 0.73876);
	GaussianBlur(image, gaussian_out_lib, Size(5, 5), 0.73876);
	imshow("Original image", image);
	imshow("Convolusion image", convolusion_out);
	imshow("Gaussian blur library image", gaussian_out_lib);
	imshow("Gaussian blur image", gaussian_out);
	waitKey(0);
	return 0;
}