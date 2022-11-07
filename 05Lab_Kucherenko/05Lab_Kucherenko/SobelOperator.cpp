#include "SobelOperator.h"
#include <iostream>
#include <ostream>
using namespace cv;
template <class InputType, class OutputType>
void convolution(const InputType* in_image, const double* mask, int ksize, OutputType* out_image, int rows, int cols, double koef = 1, bool ignoreNegVal = true) {
	int sum = 0;
	int* temp = new int[rows * cols];

	for (int i = 0; i < rows * cols; i++)
		temp[i] = in_image[i];

	for (int i = ksize / 2; i < rows - ksize / 2; i++) {
		for (int j = 0; j < cols - ksize / 2; j++) {
			sum = 0;
			for (int a = 0; a < ksize; a++) {
				for (int b = 0; b < ksize; b++) {
					sum += in_image[(i + a - ksize / 2) * cols + j - b - ksize / 2] * mask[a * ksize + b];
				}
			}
			temp[i * cols + j] = sum * koef;
		}
	}
	if (!ignoreNegVal) {
		for (size_t i = 0; i < rows * cols; i++)
			out_image[i] = temp[i];
	} else {
		for (int i = 0; i < rows * cols; i++) {
			int val = temp[i];
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			out_image[i] = val;
		}
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
	convolution<unsigned char, unsigned char>(in_image.data, mask, ksize, out_image.data, in_image.rows, in_image.cols, 1 / sum);
	delete[] mask;
}

void sobel_operator(const Mat& in_image, Mat& out_image, int* g_x, int* g_y) {
	Mat temp = in_image.clone();
	gaussian_blur(in_image, temp, 3, 1.8);
	const double sobel_xmask[] = { -0.25, 0, 0.25, -0.5, 0, 0.5,-0.25, 0, 0.25 };
	const double sobel_ymask[] = { -0.25, -0.5, 0.25,0, 0, 0,-0.25, 0.5, 0.25 };
	convolution<unsigned char, int>(temp.data, sobel_xmask, 3, g_x, in_image.rows, in_image.cols, 1, false);
	convolution<unsigned char, int>(temp.data, sobel_ymask, 3, g_y, in_image.rows, in_image.cols, 1, false);

	for (size_t i = 0; i < in_image.total(); i++) {
		int temp_pyth = static_cast<int>(sqrt(pow(g_x[i], 2) + pow(g_y[i], 2)));
		if (temp_pyth > 255)
			temp_pyth = 255;
		out_image.data[i] = static_cast<unsigned char>(temp_pyth);
	}
}
void sobel_operator(const Mat& in_image, Mat& out_image) {
	Mat temp = in_image.clone();
	gaussian_blur(in_image, temp, 3, 2);
	const double sobel_xmask[] = { -1, 0, 1, -2, 0, 2,-1, 0, 1 };
	const double sobel_ymask[] = { -1, -2, 1,0, 0, 0,-1, 2, 1 };
	int* g_x = new int[in_image.total()];
	int* g_y = new int[in_image.total()];
	convolution<unsigned char, int>(temp.data, sobel_xmask, 3, g_x, in_image.rows, in_image.cols, 1, false);
	convolution<unsigned char, int>(temp.data, sobel_ymask, 3, g_y, in_image.rows, in_image.cols, 1, false);

	for (size_t i = 0; i < in_image.total(); i++) {
		int temp_pyth = static_cast<int>(sqrt(pow(g_x[i], 2) + pow(g_y[i], 2)));
		if (temp_pyth > 255)
			temp_pyth = 255;
		out_image.data[i] = static_cast<unsigned char>(temp_pyth);
	}
}

