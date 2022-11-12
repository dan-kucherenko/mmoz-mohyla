#include "OptimalThreshold.h"

double nu_zero(int threshold_av, const cv::Mat& histogram)
{
	double sum_first = 0, sum_second = 0;
	for (int i = 0; i < threshold_av; i++) {
		sum_first += i * histogram.data[i];
		sum_second += histogram.data[i];
	}
	return sum_first / sum_second;
}

double nu_first(int threshold_av, const cv::Mat& histogram)
{
	double sum_first = 0, sum_second = 0;
	for (int i = threshold_av + 1; i < 255; i++) {
		sum_first += i * histogram.data[i];
		sum_second += histogram.data[i];
	}
	return sum_first / sum_second;
}


void optimal_threshold(const cv::Mat& input, cv::Mat& output)
{
	double nu_zero_val = nu_zero(128, input);
	double nu_first_val = nu_first(128, input);
	while (true)
	{
		
	}
}
