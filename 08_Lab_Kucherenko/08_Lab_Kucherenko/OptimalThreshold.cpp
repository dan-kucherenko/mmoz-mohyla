#include <opencv2/core.hpp>
#include "OptimalThreshold.h"

int* get_histogram(const cv::Mat& input) {
	const size_t size_hist = 256;
	const size_t size_data = input.total();
	int* hist = new int[size_hist];
	for (size_t i = 0; i < size_hist; i++)
		hist[i] = 0;
	for (int i = 0; i < size_data; i++) {
		const int value = input.data[i];
		hist[value]++;
	}
	return hist;
}

int get_optimal_threshold(const int* histogram) {
	int threshold_start = 255 / 2, new_threshold_av = 1;
	double sum_first_mu_zero = 0, sum_second_mu_zero = 0, sum_first_mu_first = 0, sum_second_mu_first = 0, mu_zero_val = 0, mu_first_val = 0;
	while (threshold_start != new_threshold_av) {
		threshold_start = new_threshold_av;
		for (int i = 0; i < threshold_start; i++) {
			sum_first_mu_zero += i * histogram[i];
			sum_second_mu_zero += histogram[i];
			mu_zero_val = sum_first_mu_zero / sum_second_mu_zero;
			if (!sum_first_mu_zero && !sum_second_mu_zero)
				mu_zero_val = 0;
		}
		for (int ii = threshold_start + 1; ii < 255; ii++) {
			sum_first_mu_first += ii * histogram[ii];
			sum_second_mu_first += histogram[ii];
			mu_first_val = sum_first_mu_first / sum_second_mu_first;
			if (!sum_first_mu_first && !sum_second_mu_first)
				mu_first_val = 0;
		}
		new_threshold_av = static_cast<int>((mu_zero_val + mu_first_val) / 2);
	}
	return new_threshold_av;
}

void reject_useless_pixels(cv::Mat& input, const int optimal_threshold) {
	for (size_t i = 0; i < input.total(); i++) {
		uchar* cur_pixel = &input.data[i];
		if (*cur_pixel < optimal_threshold)
			*cur_pixel = 0;
	}
}

void optimal_threshold(const cv::Mat& input, cv::Mat& output) {
	output = input.clone();
	const int* histogram = get_histogram(input);
	const int optimal_threshold_val = get_optimal_threshold(histogram);
	reject_useless_pixels(output, optimal_threshold_val);
}
