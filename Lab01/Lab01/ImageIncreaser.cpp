#include <opencv2/core/core.hpp>

void increaseImageWithStep(const cv::Mat in_image, cv::Mat& out_image, int n) {
	for (int i = 0, ii = 0; i < in_image.rows && ii < out_image.rows; i++, ii += n) {
		for (int j = 0, jj = 0; j < in_image.cols && jj < out_image.cols; j++, jj += n)
			out_image.data[ii * out_image.cols + jj] = in_image.data[i * in_image.cols + j];
	}
}
void addDataToEmptyPixels(const cv::Mat in_image, cv::Mat& out_image, int n) {
	for (int i = 1; i < out_image.rows; i++) {
		for (int j = 1; j < out_image.cols; j++) {
			if (out_image.data[i * out_image.cols + j] == 205) {
				if (&out_image.data[(i + 1) * out_image.cols + j - 1] != nullptr && &out_image.data[(i - 1) * out_image.cols + j + 1] != nullptr &&
					&out_image.data[(i + 1) * out_image.cols + j + 1] != nullptr && &out_image.data[(i - 1) * out_image.cols + j - 1] != nullptr)
					out_image.data[i * out_image.cols + j] = (out_image.data[(i - 1) * out_image.cols + j - 1] +
						out_image.data[(i - 1) * out_image.cols + j + 1] +
						out_image.data[(i + 1) * out_image.cols + j - 1] + out_image.data[(i + 1) * out_image.cols + j + 1]) / 4;
				if (out_image.data[i * out_image.cols + j - 1] != 205 && out_image.data[i * out_image.cols + j + 1] != 205)
					out_image.data[i * out_image.cols + j] = (out_image.data[i * out_image.cols + j - 1] + out_image.data[i * out_image.cols + j + 1]) / 2;
				else if (out_image.data[(i + 1) * out_image.cols + j] != 205 && out_image.data[(i - 1) * out_image.cols + j] != 205)
					out_image.data[i * out_image.cols + j] = (out_image.data[(i - 1) * out_image.cols + j] + out_image.data[(i + 1) * out_image.cols + j]) / 2;
			}
		}
	}
}

void fillTheExtremePoints(const cv::Mat in_image, cv::Mat& out_image, int n) {
	for (int i = 0; i < out_image.rows; i++) {
		for (int j = 0; j < out_image.cols; j++) {
			if (j == 0)
				out_image.data[i * out_image.cols + j] = out_image.data[i * out_image.cols + j + 1];
			else if (j == out_image.cols - 1)
				out_image.data[i * out_image.cols + j] = out_image.data[i * out_image.cols + j - 1];
			else if (i == 0)
				out_image.data[i * out_image.cols + j] = out_image.data[(i + 1) * out_image.cols + j];
			else if (i == out_image.rows - 1)
				out_image.data[i * out_image.cols + j] = out_image.data[(i - 1) * out_image.cols + j];
		}
	}
}

void increaseImageScale(const cv::Mat in_image, cv::Mat& out_image, int n) {
	increaseImageWithStep(in_image, out_image, n);
	addDataToEmptyPixels(in_image, out_image, n);
	fillTheExtremePoints(in_image, out_image, n);
}
