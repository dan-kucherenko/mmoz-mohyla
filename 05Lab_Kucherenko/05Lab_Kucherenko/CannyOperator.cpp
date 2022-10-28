#include "CannyOperator.h"
#include "SobelOperator.h"

void hysteresis(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	int kernel_size = 3;
	for (int i = 0; i < input_image.rows; i++) {
		for (int j = 0; j < input_image.cols; j++) {
			unsigned char pixel = output_image.data[i * input_image.rows + j];
			if (pixel <= low_threshold)
				pixel = 0;
			else if (pixel < upper_threshold) {
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
					pixel = 0;
			}

		}
	}
}

void canny_operator(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold) {
	const double pi = 3.14159265;
	int* g_x = new int[input_image.total()];
	int* g_y = new int[input_image.total()];
	// filter input image with sobel
	sobel_operator(input_image, output_image, g_x, g_y);

	for (int y = 0; y < input_image.rows; y++) {
		for (int x = 0; x < input_image.cols; x++) {
			double theta = atan(g_y[x * input_image.rows + y] / static_cast<double>(g_x[x * input_image.rows + y]));
			
		}
	}




	delete[] g_x;
	delete[] g_y;
	// filter the pixels (below the low_threshold or between low_threshold and upper_threshold)
	hysteresis(input_image, output_image, low_threshold, upper_threshold);
}
