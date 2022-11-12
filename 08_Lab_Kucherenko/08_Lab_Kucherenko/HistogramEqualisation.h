#pragma once
#include <opencv2/core/core.hpp>

void histogram_equalisation(const cv::Mat& in_image, const cv::Mat& out_image, cv::Mat& out_histogram);