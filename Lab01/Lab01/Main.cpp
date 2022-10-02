#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageDecreaser.h"
#include "ImageIncreaser.h"

using namespace std;
using namespace cv;

int main(void) {
	const string image_name("D:/dev/MMOZ/Tif/IM1.tif");
	int rows = 512, cols = 512;
	const Mat image = imread(image_name, IMREAD_GRAYSCALE);
	if (image.data == nullptr) {
		cout << "Couldn't open or find the given image path" << endl;
		return -1;
	}
	const Mat decreased_image(image.rows / 2, image.cols / 2, CV_8UC1);
	const Mat increased_image(image.rows * 2, image.cols * 2, CV_8UC1);
	decrease_image_scale(image, decreased_image);
	increase_image_scale(image, increased_image);
	imshow("Decreased image", decreased_image);
	imshow("Increased image", increased_image);
	imshow("Default image", image);
	waitKey(0);
	return 0;
}