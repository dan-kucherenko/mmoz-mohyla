#pragma once
#include <opencv2/core/mat.hpp>
void erosion(const cv::Mat& in_image, cv::Mat& out_image);
void getBorders(const cv::Mat& in_image, cv::Mat& out_image);
