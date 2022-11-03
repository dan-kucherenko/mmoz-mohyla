#include "Erosion.h"

bool check_erosion_primitive(const unsigned char* cur_pixel, const short primitive[], const short primitive_size) {
	bool checked = false;
	short x = 1, y = 1;
	if (*cur_pixel == primitive[y * primitive_size + x] &&
		*(cur_pixel - 4) == primitive[(y - 1) * primitive_size + (x - 1)] &&
		*(cur_pixel - 3) == primitive[(y - 1) * primitive_size + x] &&
		*(cur_pixel - 2) == primitive[(y - 1) * primitive_size + (x + 1)] &&
		*(cur_pixel - 1) == primitive[y * primitive_size + (x - 1)] &&
		*(cur_pixel + 1) == primitive[y * primitive_size + (x + 1)] &&
		*(cur_pixel + 2) == primitive[(y + 1) * primitive_size + (x + 1)] &&
		*(cur_pixel + 3) == primitive[(y + 1) * primitive_size + x] &&
		*(cur_pixel + 4) == primitive[(y + 1) * primitive_size + (x + 1)])
		checked = true;
	return checked;
}

void erosion(const cv::Mat& in_image, cv::Mat& out_image) {
	out_image = in_image.clone();
	const short primitive[9] = {
		255,255,255,
		255,255,255,
		255,255,255
	};

	const short primitive_size = 3;
	for (int y = 0; y < in_image.rows; y++) {
		for (int x = 0; x < in_image.cols; x++) {
			const unsigned char* cur_input_pixel = &in_image.data[x * in_image.rows + y];
			unsigned char* cur_output_pixel = &out_image.data[x * in_image.rows + y];

			if (check_erosion_primitive(cur_input_pixel, primitive, primitive_size))
				*cur_output_pixel = 255;
			else 
				*cur_output_pixel = 0;
		}
	}
}

