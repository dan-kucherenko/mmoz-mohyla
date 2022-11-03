#include "Erosion.h"

#include <iostream>

bool check_erosion_primitive(const unsigned char* cur_pixel, short x, short y, const short primitive[], const short primitive_size) {
	bool checked = false;
	if (*cur_pixel == primitive[y * primitive_size + x] &&
		*(cur_pixel - 4) == primitive[(y - 1) * primitive_size + x - 1] &&
		*(cur_pixel - 3) == primitive[(y - 1) * primitive_size + x] &&
		*(cur_pixel - 2) == primitive[(y - 1) * primitive_size + x + 1] &&
		*(cur_pixel - 1) == primitive[y * primitive_size + x - 1] &&
		*(cur_pixel + 1) == primitive[y * primitive_size + x + 1] &&
		*(cur_pixel + 2) == primitive[(y + 1) * primitive_size + x + 1] &&
		*(cur_pixel + 3) == primitive[(y + 1) * primitive_size + x] &&
		*(cur_pixel + 4) == primitive[(y + 1) * primitive_size + x + 1])
		checked = true;
	return checked;
}

void erosion(const cv::Mat& in_image, cv::Mat& out_image) {
	out_image = in_image.clone();
	//const short primitive[9] = {
	//	255,255,255,
	//	255,255,255,
	//	255,255,255
	//};
	const short primitive[9] = {
		0,0,0,
		0,0,0,
		0,0,0
	};
	const short primitive_size = 3;
	for (int y = 1; y < in_image.rows - 1; y++) {
		for (int x = 1; x < in_image.cols - 1; x++) {
			unsigned char* cur_pixel = &out_image.data[x * in_image.rows + y];
			//std::cout <<static_cast<int>( * cur_pixel) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel - 4)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel - 3)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel - 2)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel - 1)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel + 1)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel + 2)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel + 3)) << std::endl;
			//std::cout << static_cast<int>(*(cur_pixel + 4)) << std::endl;
			for (int i = 0; i < primitive_size; i++) {
				for (int j = 0; j < primitive_size; j++) {
					if (check_erosion_primitive(cur_pixel, i, j, primitive, primitive_size)) {
						*(cur_pixel - 4) = 0;
						*(cur_pixel - 3) = 0;
						*(cur_pixel - 2) = 0;
						*(cur_pixel - 1) = 0;
						*(cur_pixel + 1) = 0;
						*(cur_pixel + 2) = 0;
						*(cur_pixel + 3) = 0;
						*(cur_pixel + 4) = 0;
					} else {
						*cur_pixel = 0;
						*(cur_pixel - 4) = 0;
						*(cur_pixel - 3) = 0;
						*(cur_pixel - 2) = 0;
						*(cur_pixel - 1) = 0;
						*(cur_pixel + 1) = 0;
						*(cur_pixel + 2) = 0;
						*(cur_pixel + 3) = 0;
						*(cur_pixel + 4) = 0;
					}
				}
			}
		}
	}
}

