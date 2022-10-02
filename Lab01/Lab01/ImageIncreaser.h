#include <opencv2/core/core.hpp>
#pragma once
void increase_image_scale(const cv::Mat& in_image,const cv::Mat& out_image, const int n = 2);
void increase_image_with_step(const cv::Mat& in_image, const cv::Mat& out_image, const int n = 2);
void add_data_to_empty_pixels(const cv::Mat& out_image);
void fill_the_extreme_points(const cv::Mat& out_image);