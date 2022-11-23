#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
std::vector<cv::Point> contour_tracing(const cv::Mat& input);
