#include <map>
#include <opencv2/opencv.hpp>
#include "Region_Growth.h"

unsigned char* starting_pixel(const cv::Mat& input, unsigned char root_pixel, std::map  <unsigned char*, bool>& marked_pix) {
	const size_t rows = input.rows;
	const size_t cols = input.cols;
	unsigned char* cur_pixel = nullptr;
	for (size_t y = 0; y < rows; ++y) {
		for (size_t x = 0; x < cols; ++x) {
			cur_pixel = &input.data[x * rows + y];
			if (*cur_pixel == root_pixel) {
				marked_pix[cur_pixel] = 1;
				return cur_pixel;
			}
		}
	}
	return cur_pixel;
}

void convolution(std::map  <unsigned char*, bool>& marked_pix, cv::Mat& output) {
	for (size_t i = 0; i < output.rows; i++) {
		for (size_t j = 0; j < output.cols; j++) {
			if (!marked_pix[&output.data[j * output.rows + i]])
				output.data[j * output.rows + i] = 0;
		}
	}
}

void check_neighbors(unsigned char* root_pixel, std::vector<unsigned char*>& neighbor_pixels, int pixel_threshold, unsigned char* seed, std::map  <unsigned char*, bool>& marked_pix) {
	const short mask_size = 4, rows = 512;
	neighbor_pixels.pop_back();
	for (int y = -mask_size/2; y < mask_size/2; y++) {
		for (int x = -mask_size/2; x < mask_size/2; x++) {
			unsigned char* neighbor_pixel = root_pixel + (x* rows + y);
			if (neighbor_pixel != root_pixel && neighbor_pixel != seed && neighbor_pixel  != nullptr) {
				if (*seed - *neighbor_pixel < pixel_threshold) {
					if (!marked_pix[neighbor_pixel]) {
						neighbor_pixels.push_back(neighbor_pixel);
						marked_pix[neighbor_pixel] = 1;
					}
				}
			}
		}
	}
}

void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold) {
	output = input.clone();
	cv::Mat temp = output.clone();
	std::map  <unsigned char*, bool> marked_pix;
	for (size_t i = 0; i < output.total(); i++)
		marked_pix[&output.data[i]] = 0;
	std::vector<unsigned char*> av_pixels;
	unsigned char* seed = starting_pixel(output, root_pixel_br, marked_pix);
	av_pixels.push_back(seed);
	check_neighbors(av_pixels[0], av_pixels, pixel_threshold, seed, marked_pix);
	while (!av_pixels.empty())
		check_neighbors(av_pixels[av_pixels.size() - 1], av_pixels, pixel_threshold, seed, marked_pix);
	convolution(marked_pix, output);
}

void region_growth(const cv::Mat& input, cv::Mat& output, size_t pixel_x, size_t pixel_y, int pixel_threshold) {
	output = input.clone();
	cv::Mat temp = output.clone();
	std::map  <unsigned char*, bool> marked_pix;
	for (size_t i = 0; i < output.total(); i++)
		marked_pix[&output.data[i]] = 0;
	std::vector<unsigned char*> av_pixels;
	unsigned char* seed = &output.data[pixel_x * input.rows + pixel_y];
	av_pixels.push_back(seed);
	check_neighbors(av_pixels[0], av_pixels, pixel_threshold, seed, marked_pix);
	while (!av_pixels.empty())
		check_neighbors(av_pixels[av_pixels.size() - 1], av_pixels, pixel_threshold, seed, marked_pix);
	convolution(marked_pix, output);
}
