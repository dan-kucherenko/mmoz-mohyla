#pragma once
#include <opencv2/core/mat.hpp>
void convolution(const cv::Mat& in_image, const double* mask, int ksize, double koef, cv::Mat& out_image);
