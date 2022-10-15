#include "Convolution.h"
#include "GaussianBlur.h"

void gaussian_blur(const cv::Mat& in_image, cv::Mat& out_image, const int ksize, double sigma) {
	const double exp = 2.71828, pi = 3.14159;
	double sum = 0;
	double* mask = new double[ksize * ksize];
	int y = -ksize / 2;
	for (int i = 0; i < ksize; i++) {
		int x = -ksize / 2;
		for (int j = 0; j < ksize; j++) {
			mask[i * ksize + j] = 1 / (2 * pi * pow(sigma, 2)) * pow(exp, -((pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2))));
			sum += mask[i * ksize + j];
			x++;
		}
		y++;
	}
	convolution(in_image, mask, ksize, 1 / sum, out_image);
	delete[] mask;
}
