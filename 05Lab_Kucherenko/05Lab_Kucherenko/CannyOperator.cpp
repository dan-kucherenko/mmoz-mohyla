#include "CannyOperator.h"
#include "SobelOperator.h"

void hysteresis(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	for (int i = 0; i < input_image.rows; i++) {
		for (int j = 0; j < input_image.cols; j++) {
			unsigned char pixel = output_image.data[i * input_image.rows + j];
			if (pixel <= low_threshold)
				pixel = 0;
			else if (pixel < upper_threshold) {
				for (int ii = 0; ii < 3; ii++) {
					for (int jj = 0; jj < 3; jj++) {
						if (output_image.data[ii * input_image.rows + jj] > upper_threshold) {
							break;
						}
					}
				}
			}

		}
	}
}

void canny_operator(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	const double pi = 3.14159265;
	sobel_operator(input_image, output_image);
	/*
	 * int ksize = 3;
	 * int ksizeDelta = ksize /2;
	 */




	 // filter the pixels (below the low_threshold or between low_threshold and upper_threshold)
	hysteresis(input_image, output_image, low_threshold, upper_threshold);
}
