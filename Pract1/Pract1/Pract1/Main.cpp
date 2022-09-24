#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>



int main() {
	std::string str = "Image";
	std::string imageName("D:/dev/MMOZ/Tif/IM1.tif");
	int rows = 512;
	int cols = 512;
	cv::Mat Image;

	//cv::IMREAD_COLOR
	Image = cv::imread(imageName.c_str(), cv::IMREAD_GRAYSCALE);
	cv::Mat gray(rows, cols, CV_8UC1, cv::Scalar(120));


	//cv::Mat gray(rows, cols, CV_8UC1, cv::Scalar(0));

	// Check for invalid input
	if (Image.data == 0) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// Image = gray.clone();
	for (int i = 20; i < Image.rows; i++)
		for (int j = 0; j < Image.cols - 20; j++) {
			Image.data[i * Image.cols] = 255;
		}
	cv :: Mat out = Image.clone();
	cv::imshow("Windows window", gray);                // Show our image inside it.
	cv::imshow("Display window", Image);                // Show our image inside it.

	cv::waitKey(0); // Wait for a keystroke in the window


	system("Pause");
	return 0;
}
