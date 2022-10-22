#include "SobelOperator.h"

#include <iostream>
#include <ostream>
using namespace cv;
void convolution(const Mat& in_image, const double* mask, int ksize, Mat& out_image, bool ignoreNegVal, double koef = 1) {
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
	//for (int i = 0; i < in_image.rows; i++) {
	//	for (int j = 0; j < in_image.cols; j++)
	//		std::cout << *(temp+i);
	//	std::cout << std::endl;
	//}
	if (!ignoreNegVal) {
		for (int i = 0; i < in_image.rows * in_image.cols; i++) {
			int val = temp[i];
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			out_image.data[i] = val;
		}
	} else {
		for (size_t i = 0; i < in_image.total(); i++)
			out_image.data[i] = temp[i];
	}
	delete[]temp;
}

void gaussian_blur(const Mat& in_image, Mat& out_image, const int ksize, double sigma) {
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
	convolution(in_image, mask, ksize, out_image, false, 1 / sum);
	delete[] mask;
}

void sobel_operator(const Mat& in_image, Mat& out_image, Mat& g_x, Mat& g_y) {
	Mat temp = in_image.clone();
	gaussian_blur(in_image, temp, 5, 0.9);
	const double sobel_xmask[] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	const double sobel_ymask[] = {
		-1, -2, 1,
		0, 0, 0,
		-1, 2, 1
	};
	/*Mat g_x(in_image.rows, in_image.cols, CV_32F, Scalar(0));
	Mat g_y(in_image.rows, in_image.cols, CV_32F, Scalar(0));*/
	convolution(temp, sobel_xmask, 3, g_x, true);
	convolution(temp, sobel_ymask, 3, g_y, true);

	for (size_t i = 0; i < in_image.total(); i++) {
		int temp_pyth = sqrt(pow(g_x.data[i], 2) + pow(g_y.data[i], 2));
		if (temp_pyth > 255)
			temp_pyth = 255;
		out_image.data[i] = temp_pyth;
	}
}
