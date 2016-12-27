#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat img = cv::imread("E:e.jpg");
	cv::imshow("IMG", img);
	cv::waitKey();

	return 0;
}