#pragma once
#include <opencv2/core/mat.hpp>
void gaussian_blur(const cv::Mat& in_image, cv::Mat& out_image, int ksize, double sigma);