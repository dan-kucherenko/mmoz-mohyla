#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageDecreaser.h"
#include "ImageIncreaser.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("D:/dev/MMOZ/Tif/IM1.tif");
	int rows = 512, cols = 512;
	Mat image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Couldn't open or find the given image path" << endl;
		return -1;
	}
	Mat decreasedImage(image.rows / 2, image.cols / 2, CV_8UC1);
	Mat increasedImage(image.rows * 2, image.cols * 2, CV_8UC1, Scalar(25));
	decreaseImageScale(image, decreasedImage);
	increaseImageScale(image, increasedImage);
	imshow("Decreased image", decreasedImage);
	imshow("Increased image", increasedImage);
	imshow("Default image", image);
	waitKey(0);
	return 0;
}