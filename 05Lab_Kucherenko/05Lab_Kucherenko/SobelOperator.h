#pragma once
#include <opencv2/core/mat.hpp>
void sobel_operator(const cv::Mat& in_image, cv::Mat& out_image, int* g_x, int* g_y);
void sobel_operator(const cv::Mat& in_image, cv::Mat& out_image);