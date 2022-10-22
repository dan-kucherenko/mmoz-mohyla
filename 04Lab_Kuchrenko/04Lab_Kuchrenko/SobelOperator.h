#pragma once
#include <opencv2/core/mat.hpp>
void sobel_operator(const cv::Mat& in_image, cv::Mat& out_image, cv::Mat& g_x, cv::Mat& g_y);
