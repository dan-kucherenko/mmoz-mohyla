#pragma once
#include <opencv2/core/mat.hpp>
void canny_operator(const cv::Mat& input_image, cv::Mat& output_image, int low_threshold, int upper_threshold);
