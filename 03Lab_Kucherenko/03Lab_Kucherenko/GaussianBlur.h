#pragma once
#include <opencv2/core/mat.hpp>
void gaussianBlur(const cv::Mat& in_image, cv::Mat& out_image, int ksize, double sigma);