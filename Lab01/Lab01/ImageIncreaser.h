#include <opencv2/core/core.hpp>
#pragma once
void increaseImageScale(const cv::Mat in_image, cv::Mat& out_image, int n = 2);
void increaseImageWithStep(const cv::Mat in_image, cv::Mat& out_image, int n = 2);
void addDataToEmptyPixels(const cv::Mat in_image, cv::Mat& out_image, int n = 2);
void fillTheExtremePoints(const cv::Mat in_image, cv::Mat& out_image, int n = 2);