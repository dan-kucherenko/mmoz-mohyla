#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "HistogramEqualisation.h"
#include "HistogramBuilder.h"

using namespace std;
using namespace cv;

int main(void) {
	string str = "Image";
	string imageName("D:/dev/VisualStudioCode/mmoz-mohyla/02Lab/02Lab/Geneva.tif");
	Mat in_image = imread(imageName, IMREAD_GRAYSCALE);
	if (in_image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat histogram_in, histogram_out;
	Mat out_image(in_image.rows, in_image.cols, CV_8UC1, Scalar(0));
	histogram_equalisation(in_image, out_image, histogram_in, histogram_out);
	imshow("Default image", in_image);
	imshow("Equalised image", out_image);
	imshow("Histogram of the original image", histogram_in);
	imshow("Histogram of the equalised image", histogram_out);
	waitKey(0);
	return 0;
}