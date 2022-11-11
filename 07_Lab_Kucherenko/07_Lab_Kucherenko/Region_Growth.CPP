#include "Region_Growth.h"

unsigned char starting_pixel(const cv::Mat& input, unsigned char root_pixel) {
	const size_t rows = input.rows;
	const size_t cols = input.cols;
	unsigned char cur_pixel = 0;
	for (size_t y = 0; y < rows; ++y) {
		for (size_t x = 0; x < cols; ++x) {
			cur_pixel = input.data[x * rows + y];
			if (cur_pixel == root_pixel) {
				return cur_pixel;
			}
		}
	}
	return cur_pixel;
}

void check_neighbors(unsigned char* root_pixel, std::vector<unsigned char>& neighbor_pixels, int pixel_threshold, unsigned char seed) {
	const short mask_size = 4;
	neighbor_pixels.pop_back();
	for (int i = -mask_size; i < mask_size; i++) {
		unsigned char neighbor_pixel = *(root_pixel + i);
		if (&seed != &neighbor_pixel) {
			if (seed - neighbor_pixel < pixel_threshold)
				neighbor_pixels.push_back(neighbor_pixel);
			else
				*root_pixel = 0;
		}
	}
}




void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold) {
	output = input.clone();
	std::vector<unsigned char> av_pixels;
	unsigned char seed = starting_pixel(output, root_pixel_br);
	av_pixels.push_back(seed);
	for (size_t i = 0; i < av_pixels.size(); i++)
		check_neighbors(&av_pixels[i], av_pixels, pixel_threshold, seed);
}
