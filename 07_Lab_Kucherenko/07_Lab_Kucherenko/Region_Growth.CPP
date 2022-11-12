#include "Region_Growth.h"

#include <iostream>

unsigned char* starting_pixel(const cv::Mat& input, unsigned char root_pixel) {
	const size_t rows = input.rows;
	const size_t cols = input.cols;
	unsigned char* cur_pixel = nullptr;
	for (size_t y = 0; y < rows; ++y) {
		for (size_t x = 0; x < cols; ++x) {
			cur_pixel = &input.data[x * rows + y];
			if (*cur_pixel == root_pixel) {
				return cur_pixel;
			}
		}
	}
	return cur_pixel;
}

bool pixel_alr_added(unsigned char* pixel, std::vector<unsigned char*>& neighbor_pixels) {
	for (auto element : neighbor_pixels) {
		if (element == pixel) {
			return true;
		}
	}
	return false;
}

void check_neighbors(unsigned char* root_pixel, std::vector<unsigned char*>& neighbor_pixels, int pixel_threshold, unsigned char* seed, int& curr_size) {
	const short mask_size = 4;
	neighbor_pixels.pop_back();
	curr_size--;
	for (int i = -mask_size; i <= mask_size; i++) {
		unsigned char* neighbor_pixel = root_pixel + i;
		if (neighbor_pixel != root_pixel && neighbor_pixel != seed) {
			if (*seed - *neighbor_pixel < pixel_threshold) {
				if (!pixel_alr_added(neighbor_pixel, neighbor_pixels)) {
					neighbor_pixels.push_back(neighbor_pixel);
					curr_size++;
				}
			}
			else
				*neighbor_pixel = 0;
		}
		//delete neighbor_pixel;d
	}
}




void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold) {
	int size = 0;
	int curr_size;
	output = input.clone();
	std::vector<unsigned char*> av_pixels;
	unsigned char* seed = starting_pixel(output, root_pixel_br);
	av_pixels.push_back(seed);
	size++;
	curr_size = size;
	check_neighbors(av_pixels[0], av_pixels, pixel_threshold, seed, size);
	while (!av_pixels.empty()) {
		curr_size = size;
		if (curr_size + 1 < size)
			av_pixels.pop_back();
		check_neighbors(av_pixels[av_pixels.size() - 1], av_pixels, pixel_threshold, seed, size);
	}
}
//unsigned char& starting_pixel(const cv::Mat& input, unsigned char root_pixel) {
//	const size_t rows = input.rows;
//	const size_t cols = input.cols;
//	unsigned char cur_pixel;
//	for (size_t y = 0; y < rows; ++y) {
//		for (size_t x = 0; x < cols; ++x) {
//			cur_pixel = input.data[x * rows + y];
//			if (cur_pixel == root_pixel) {
//				return cur_pixel;
//			}
//		}
//	}
//	return cur_pixel;
//}
//
//bool pixel_alr_added(unsigned char& pixel, std::vector<unsigned char&>& neighbor_pixels) {
//	for (auto element : neighbor_pixels) {
//		if (element == pixel) {
//			return true;
//		}
//	}
//	return false;
//}
//
//void check_neighbors(unsigned char& root_pixel, std::vector<unsigned char&>& neighbor_pixels, int pixel_threshold, unsigned char* seed) {
//	const short mask_size = 4;
//	neighbor_pixels.pop_back();
//	for (int i = -mask_size; i <= mask_size; i++) {
//		unsigned char neighbor_pixel = root_pixel + i;
//		if (neighbor_pixel != &root_pixel) {
//			if (*seed - *neighbor_pixel < pixel_threshold) {
//				if (!pixel_alr_added(*neighbor_pixel, neighbor_pixels))
//					neighbor_pixels.push_back(&neighbor_pixel);
//			}
//			else
//				*neighbor_pixel = 0;
//		}
//		//delete neighbor_pixel;d
//	}
//}
//
//
//
//
//void region_growth(const cv::Mat& input, cv::Mat& output, unsigned char root_pixel_br, int pixel_threshold) {
//	output = input.clone();
//	std::vector<unsigned char&> av_pixels;
//	unsigned char& seed = starting_pixel(output, root_pixel_br);
//	av_pixels.push_back(&seed);
//	check_neighbors(av_pixels[0], av_pixels, pixel_threshold, seed);
//	for (size_t i = 1; i < av_pixels.size(); i++) {
//		if (av_pixels.empty())
//			break;
//		check_neighbors(av_pixels[av_pixels.size() - i], av_pixels, pixel_threshold, seed);
//	}
//	delete seed;
//}
