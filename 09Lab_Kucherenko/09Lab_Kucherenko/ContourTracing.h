#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
void contour_tracing(const cv::Mat& original, cv::Mat& boundaries, std::vector<cv::Point>& contour_points);
