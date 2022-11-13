#pragma once
void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold = 128);
void region_growth(const cv::Mat& input, cv::Mat& output, size_t pixel_x, size_t pixel_y, int pixel_threshold = 128);