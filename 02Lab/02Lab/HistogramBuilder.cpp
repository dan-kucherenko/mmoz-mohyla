#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

Mat build_histogram(Mat& image) {
	Mat src = image;
	if (!src.data) 
		return src;
	vector<Mat> plane;
	split(src, plane);
	const int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	const bool uniform = true, accumulate = false;
	Mat grayscale_hist;
	calcHist(plane.data(), 1, 0, Mat(), grayscale_hist, 1, &histSize, &histRange, uniform, accumulate);

	const int hist_w = 700; int hist_h = 600;
	const int bin_w = cvRound(static_cast<double>(hist_w) / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(grayscale_hist, grayscale_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) 
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(grayscale_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(grayscale_hist.at<float>(i))),
			Scalar(255, 0, 0), 1, 8, 0);
	return histImage;
}
