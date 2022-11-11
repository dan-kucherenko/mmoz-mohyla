#pragma once
#include <opencv2/core/mat.hpp>
void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold = 128);