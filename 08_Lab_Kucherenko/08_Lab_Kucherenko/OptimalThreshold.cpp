#include "OptimalThreshold.h"

#include <iostream>
#include <opencv2/core.hpp>

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
int get_optimal_threshold(const int* histogram)
{
	double threshold_av = 255 / 2, new_threshold_av = 1;
	double sum_first_mu_zero = 0, sum_second_mu_zero = 0, sum_first_mu_first = 0, sum_second_mu_first = 0, mu_zero_val = 0, mu_first_val = 0;
	int i = 0, ii = static_cast<int>(threshold_av) + 1;
	while (i < static_cast<int>(threshold_av) && ii < 255 && threshold_av != new_threshold_av) {
		sum_first_mu_zero += i * histogram[i];
		sum_second_mu_zero += histogram[i];
		mu_zero_val = sum_first_mu_zero / sum_second_mu_zero;

		sum_first_mu_first += ii * histogram[ii];
		sum_second_mu_first += histogram[ii];
		mu_first_val = sum_first_mu_first / sum_second_mu_first;

		new_threshold_av = (mu_zero_val + mu_first_val) / 2;
		threshold_av = new_threshold_av;
		i++;
		ii++;
	}
	return threshold_av;
}

void optimal_threshold(const cv::Mat& input, cv::Mat& output) {
	const int* histogram = get_histogram(input);
	const int optimal_threshold_val = get_optimal_threshold(histogram);
	std::cout << optimal_threshold_val << std::endl;
}
