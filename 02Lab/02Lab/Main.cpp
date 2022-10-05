#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "HistogramEqualisation.h"
#include "HistogramBuilder.h"

using namespace std;
using namespace cv;

int main(void)
{
	string str = "Image";
	string imageName("D:/dev/VisualStudioCode/mmoz-mohyla/02Lab/02Lab/Geneva.tif");
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	if (image.data == 0) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	Mat h1, h2;
	Mat out(image.rows, image.cols, CV_8UC1, Scalar(0));
	histogram_equalisation(image, out, h1, h2);
	Mat histImage = build_histogram(out);
	imshow("Default image", image);
	imshow("Equalised image", out);
	imshow("Histogram image", histImage);
	waitKey(0);
	return 0;
}