#include <iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Convolution.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("D:/dev/MMOZ/Tif/Geneva.tif");
	const int cols = 512, rows = 512;
	Mat image = imread(imageName,IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat out(image.rows, image.cols, CV_8UC1, Scalar(0));
	double mask[9] = {1,1,1,
					  1,4,1,
					  1,1,1 };
	double k = 1.0 / 12.0;
	convolution(image, mask, 3, k, out);
	imshow("Image_in", image);
	imshow("Image_out", out);
	waitKey(0);
	return 0;
}