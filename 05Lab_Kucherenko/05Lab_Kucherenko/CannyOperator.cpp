#include "CannyOperator.h"
#include "SobelOperator.h"

void hysteresis(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	int kernel_size = 3;
	for (int i = 0; i < input_image.rows; i++) {
		for (int j = 0; j < input_image.cols; j++) {
			unsigned char* pixel = &output_image.data[i * input_image.cols + j];
			if (*pixel <= low_threshold)
				*pixel = 0;
			else if (*pixel < upper_threshold) {
				bool pixelAboveUpThreshold = true;
				for (int ii = 0; ii < kernel_size - 1; ii++) {
					for (int jj = 0; jj < kernel_size - 1; jj++) {
						if (output_image.data[ii * kernel_size + jj] > upper_threshold) {
							pixelAboveUpThreshold = false;
							break;
						}
					}
				}
				if (pixelAboveUpThreshold)
					*pixel = 0;
			}

		}
	}
}

void canny_operator(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	int* g_x = new int[input_image.total()];
	int* g_y = new int[input_image.total()];
	// filter input image with sobel
	sobel_operator(input_image, output_image, g_x, g_y);

	for (int x = 1; x < input_image.rows - 1; x++) {
		for (int y = 1; y < input_image.cols - 1; y++) {
			double theta = 0;
			if (g_y[x * input_image.cols + y] != 0 || g_x[x * input_image.cols + y] != 0)
				theta = atan(g_y[x * input_image.cols + y] / static_cast<double>(g_x[x * input_image.cols + y]));
			unsigned char* pixel = &output_image.data[x * input_image.cols + y];
			unsigned char pixel_one = 0;
			unsigned char pixel_two = 0;
			if (-2 < theta && theta < 2) {
				if (theta < 1.73 && 0.57 < theta) {
					pixel_one = output_image.data[(x + 1) * input_image.cols + (y - 1)];
					pixel_two = output_image.data[(x - 1) * input_image.cols + (y + 1)];
				} else if (theta < 0.57 && -0.57 < theta) {
					pixel_one = output_image.data[x * input_image.cols + (y + 1)];
					pixel_two = output_image.data[x * input_image.cols + (y - 1)];
				} else if (-0.57 < theta && -1.73 < theta) {
					pixel_one = output_image.data[(x - 1) * input_image.cols + (y - 1)];
					pixel_two = output_image.data[(x + 1) * input_image.cols + (y + 1)];
				} else {
					pixel_one = output_image.data[(x - 1) * input_image.cols + y];
					pixel_two = output_image.data[(x + 1) * input_image.cols + y];
				}
			}
			if (pixel_one > *pixel || pixel_two > *pixel) {
				*pixel = 0;
			}
		}
	}
	delete[] g_x;
	delete[] g_y;
	// filter the pixels (below the low_threshold or between low_threshold and upper_threshold)
	hysteresis(input_image, output_image, low_threshold, upper_threshold);
}
