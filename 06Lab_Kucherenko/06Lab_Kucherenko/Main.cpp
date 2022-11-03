#include <iostream>
#include <opencv2/opencv.hpp>
#include "Erosion.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("D:/dev/MMOZ/Tif/contour.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat erosed_image(image.rows, image.cols, CV_8UC1, Scalar(0));
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	erosion(image, erosed_image);
	imshow("Input image", image);
	imshow("Erosed image", erosed_image);
	waitKey(0);
	return 0;
}