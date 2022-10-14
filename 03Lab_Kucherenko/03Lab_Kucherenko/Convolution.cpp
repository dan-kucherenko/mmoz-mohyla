#include "Convolution.h"

void convolution(const cv::Mat& in_image, const double* mask, int ksize, double koef, cv::Mat& out_image) {
	int sum = 0;
	int* temp = new int[in_image.total()];

	for (int i = 0; i < in_image.total(); i++)
		temp[i] = in_image.data[i];

	for (int i = ksize / 2; i < in_image.rows - ksize / 2; i++) {
		for (int j = 0; j < in_image.cols - ksize / 2; j++) {
			sum = 0;
			for (int a = 0; a < ksize; a++) {
				for (int b = 0; b < ksize; b++) {
					sum += in_image.data[(i + a - ksize / 2) * in_image.cols + j - b - ksize / 2] * mask[a * ksize + b];
				}
			}
			temp[i * in_image.cols + j] = sum * koef;
		}
	}
	for (int i = 0; i < in_image.rows * in_image.cols; i++) {
		int val = temp[i];
		if (val < 0)
			val = 0;
		if (val > 255)
			val = 255;
		out_image.data[i] = val;
	}
	delete[]temp;
}
