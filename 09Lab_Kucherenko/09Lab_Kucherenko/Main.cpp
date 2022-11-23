#include <iostream>
#include <opencv2/opencv.hpp>
#include "ContourTracing.h"

using namespace std;
using namespace cv;

int main(void) {
	string imageName("D:/dev/MMOZ/Tif/IM5.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	std::vector<Point> contour;
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	std::vector<Point> contour = contour_tracing(image);
	//imshow("Input image", image);
	//imshow("Image after optimal thresholding", optimal_thresholded);
	waitKey(0);
	return 0;
}