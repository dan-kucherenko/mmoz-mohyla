#include <opencv2/core/core.hpp>

void increaseImageScale(const cv::Mat in_image, cv::Mat& out_image, int n) {
	for (int i = 0, ii = 0; i < in_image.rows && ii < out_image.rows; i++, ii += n) {
		for (int j = 0, jj = 0; j < in_image.cols && jj < out_image.cols; j++, jj += n)
			out_image.data[ii * out_image.cols + jj] = in_image.data[i * in_image.cols + j];
	}
}
