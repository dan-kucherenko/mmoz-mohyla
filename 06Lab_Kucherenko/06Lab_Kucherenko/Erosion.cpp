#include "Erosion.h"

bool check_erosion_primitive(const unsigned char* cur_pixel, const short primitive[], const short primitive_size) {
	bool checked = false;
	short x = 1, y = 1;
	if (*(cur_pixel - 4) == primitive[x - 1] &&
		*(cur_pixel - 3) == primitive[x] &&
		*(cur_pixel - 2) == primitive[x + 1] &&
		*cur_pixel == primitive[y * primitive_size + x] &&
		*(cur_pixel - 1) == primitive[y * primitive_size] &&
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
			/*for (int i = -pow(primitive_size, 2) / 2, j = 0; i < pow(primitive_size, 2) / 2 && j < pow(primitive_size, 2); i++, j++) {
				if (*(cur_output_pixel + i) != primitive[j]) {
					*cur_output_pixel = 0;
					break;
				}
				*cur_output_pixel = 255;
			}*/
			if (check_erosion_primitive(cur_input_pixel, primitive, primitive_size))
				*cur_output_pixel = 255;
			else
				*cur_output_pixel = 0;
		}
	}
}

void getBorders(const cv::Mat& in_image, cv::Mat& out_image) {
	cv::Mat temp(in_image.rows, in_image.cols, CV_8UC1, cv::Scalar(0));
	erosion(in_image, temp);
	out_image = in_image.clone();
	for (int y = 0; y < in_image.rows; y++) {
		for (int x = 0; x < in_image.cols; x++) {
			if (in_image.data[x * in_image.rows + y] > temp.data[x * in_image.rows + y])
				out_image.data[x * in_image.rows + y] = 255;
			else
				out_image.data[x * in_image.rows + y] = 0;
		}
	}
}
