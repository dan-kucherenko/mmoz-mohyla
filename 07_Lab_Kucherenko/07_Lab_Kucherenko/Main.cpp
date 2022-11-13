#include <iostream>
#include <opencv2/opencv.hpp>
#include "Region_Growth.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("C:/dev/MMOZ/Tif/IM11.tif");
	//string imageName("C:/dev/MMOZ/Tif/contour.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat marked_image(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat marked_image_coord(image.rows, image.cols, CV_8UC1, Scalar(0));
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	region_growth(image, marked_image, 128, 100);
	region_growth(image, marked_image_coord, 150, 200, 80);
	imshow("Input image", image);
	imshow("Image after marking alg.", marked_image);
	imshow("Image (coord) after marking alg.", marked_image_coord);
	waitKey(0);
	return 0;
}