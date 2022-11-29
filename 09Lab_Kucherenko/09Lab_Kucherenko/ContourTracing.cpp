#include "ContourTracing.h"

#include <iostream>

cv::Point find_start_p(const cv::Mat& input) {
	cv::Point start(0, 0);
	for (int i = input.total() - 1; i >= 0; i--) {
		if (input.data[i]) {
			start.x = i / input.cols;
			start.y = i % input.cols;
			break;
		}
	}
	return start;
}

void calculate_temp_dir(const int& dir, int& temp_dir) {
	if (!(dir % 2)) // for odd directions
		temp_dir = (dir + 7) % 8;
	else			// for even directions
		temp_dir = (dir + 6) % 8;
}

void contour_tracing_hlpr(const cv::Mat& input, cv::Mat& contour, const int& x, const int& y, std::vector<cv::Point>& contour_vec, int& dir, int& temp_dir) {
	cv::Point temp_point;
	switch (temp_dir) { // switch case for every direction
	case 0:
		if (y + 1 < input.cols && input.data[x * input.cols + (y + 1)]) {
			temp_point.x = x;
			temp_point.y = y + 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 0;
			calculate_temp_dir(dir, temp_dir);
		} else {
			dir = 0;
			temp_dir = 1;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 1:
		if (x - 1 >= 0 && y + 1 < input.cols && input.data[(x - 1) * input.cols + (y + 1)]) {
			temp_point.x = x - 1;
			temp_point.y = y + 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 1;
			calculate_temp_dir(dir, temp_dir);

		} else {
			dir = 1;
			temp_dir = 2;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 2:
		if (x - 1 >= 0 && input.data[(x - 1) * input.cols + y] == 255) {
			temp_point.x = x - 1;
			temp_point.y = y;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 2;
			calculate_temp_dir(dir, temp_dir);

		} else {
			dir = 2;
			temp_dir = 3;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 3:
		if (x - 1 >= 0 && y - 1 >= 0 && input.data[(x - 1) * input.cols + (y - 1)]) {
			temp_point.x = x - 1;
			temp_point.y = y - 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 3;
			calculate_temp_dir(dir, temp_dir);

		} else {
			dir = 3;
			temp_dir = 4;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 4:
		if (y - 1 >= 0 && input.data[x * input.cols + (y - 1)] == 255) {
			temp_point.x = x;
			temp_point.y = y - 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 4;
			calculate_temp_dir(dir, temp_dir);

		} else {
			dir = 4;
			temp_dir = 5;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 5:
		if (x + 1 < input.rows && y - 1 >= 0 && input.data[(x + 1) * input.cols + (y - 1)]) {
			temp_point.x = x + 1;
			temp_point.y = y - 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 5;
			calculate_temp_dir(dir, temp_dir);

		}
		else {
			dir = 5;
			temp_dir = 6;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 6:
		if (x + 1 < input.rows && input.data[(x + 1) * input.cols + y]) {
			temp_point.x = x + 1;
			temp_point.y = y;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 6;
			calculate_temp_dir(dir, temp_dir);
		}
		else {
			dir = 6;
			temp_dir = 7;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	case 7:
		if (x + 1 < input.rows && y + 1 < input.cols && input.data[(x + 1) * input.cols + (y + 1)] ) {
			temp_point.x = x + 1;
			temp_point.y = y + 1;
			contour_vec.push_back(temp_point);
			contour.data[temp_point.x * input.cols + temp_point.y] = 255;
			dir = 7;
			calculate_temp_dir(dir, temp_dir);
		}
		else {
			dir = 7;
			temp_dir = 0;
			contour_tracing_hlpr(input, contour, x, y, contour_vec, dir, temp_dir);
		}
		break;
	default:
		std::cout << "No case were approved" << std::endl;
	}
}

void contour_tracing(const cv::Mat& original, cv::Mat& boundaries, std::vector<cv::Point>& contour_points) {
	const cv::Point start = find_start_p(original);
	contour_points.push_back(start);
	int dir = 7;
	int temp_dir = (dir + 6) % 8;
	while (!(contour_points.at(0).x == contour_points.at(contour_points.size() - 1).x && contour_points.at(0).y == contour_points.at(contour_points.size() - 1).y && contour_points.size() >= 2)) {
		cv::Point temp_point = contour_points.at(contour_points.size() - 1);
		contour_tracing_hlpr(original, boundaries, temp_point.x, temp_point.y, contour_points, dir, temp_dir);
	}
}

