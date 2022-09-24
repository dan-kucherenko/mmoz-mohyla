#include "ImageDecreaser.h"

void decreaseImageScale(const cv::Mat in_image, cv::Mat& out_image, int n) {
    for (int i = 0, ii = 0; i < out_image.rows && ii < in_image.rows; i++, ii += n) {
        for (int j = 0, jj = 0; j < out_image.cols && j < in_image.cols; j++, jj += n)
            out_image.data[i * out_image.cols * j] = in_image.data[ii * in_image.cols * jj];
    }
}