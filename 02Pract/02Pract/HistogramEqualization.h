#pragma once
#include <opencv2/core/core.hpp>

void histogramEqualization(const cv::Mat& in_image, cv::Mat& out_image, cv::Mat& in_histogram, cv::Mat& out_histogram);