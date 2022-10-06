#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include "HistogramBuilder.h"

void histogram_equalisation(const cv::Mat& in_image, const cv::Mat& out_image, cv::Mat& in_histogram, cv::Mat& out_histogram) {
	const size_t size_hist = 256;
	const size_t size_data = in_image.rows * in_image.cols;
	const float alpha = 255.0 / size_data;
	int* hist = new int[size_hist];
	int* hist_cum = new int[size_hist];
	for (int i = 0; i < size_hist; i++) {
		hist[i] = 0;
		hist_cum[i] = 0;
	}
	for (int i = 0; i < size_data; i++) {
		const int value = in_image.data[i];
		hist[value]++;
	}
	hist_cum[0] = hist[0];
	for (int i = 1; i < size_hist; i++)
		hist_cum[i] = hist[i] + hist_cum[i - 1];
	for (int i = 0; i < size_data; i++) {
		const int value = in_image.data[i];
		out_image.data[i] = hist_cum[value] * alpha;
	}
	delete[]hist_cum;
	delete[]hist;
	// plotting the histogram
	in_histogram = build_histogram(in_image);
	out_histogram = build_histogram(out_image);
}

