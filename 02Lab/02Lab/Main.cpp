#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "HistogramEqualisation.h"

using namespace std;
using namespace cv;

int main(void)
{
	string str = "Image";
	string imageName("D:/dev/MMOZ/Tif/Geneva.tif");
	const int cols = 512, rows = 512;
	Mat image = imread(imageName.c_str(), cv::IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat h1, h2;
	Mat out(image.rows, image.cols, CV_8UC1, Scalar(0));
	histogram_equalisation(image, out, h1, h2);
	imshow("Image_in", image);
	imshow("Image_out", out);
	waitKey(0);
	return 0;
}