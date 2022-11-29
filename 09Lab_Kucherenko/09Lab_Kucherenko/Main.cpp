#include <iostream>
#include <opencv2/opencv.hpp>
#include "ContourTracing.h"

using namespace std;
using namespace cv;

int main(void) {
	string imageName("C:/dev/MMOZ/Tif/contour.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat contour(image.cols, image.rows, CV_8UC1, Scalar(0));
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	std::vector<Point> contour_points;
	contour_tracing(image, contour, contour_points);
	imshow("Input image", image);
	imshow("Image contour", contour);
	waitKey(0);
	return 0;
}