#include "CircleDetector.h"
#include <opencv2/opencv.hpp>

void CircleDetector::process(const cv::Mat &input, cv::Mat &output)
{
	cv::Mat gray, gray_blur;
	cv::cvtColor(input, gray, CV_BGR2GRAY);
	cv::GaussianBlur(gray, gray_blur, cv::Size(5,5), 1.5);
	std::vector<cv::Vec3f> circles;

	cv::HoughCircles(gray_blur, circles, CV_HOUGH_GRADIENT,
					 2, 150, 200, 100, 25, 100);

	input.copyTo(output);
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//»æÖÆÔ²ÐÄ  
		cv::circle(output, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		//»æÖÆÔ²ÂÖÀª  
		cv::circle(output, center, radius, cv::Scalar(155, 50, 255), 2, 8, 0);
	}

	//std::cout << circles.size() << std::endl;
	float averageY = -0.0;
	if(circles.size() == 6)
	{
		averageY = (circles[0][1]+circles[1][1]+circles[2][1]+
			circles[3][1]+circles[4][1]+circles[5][1])/6;
		_circleCenterPointsY.push_back(averageY);	
	}
	else
	{
		_circleCenterPointsY.push_back(-0.0);
	}
	std::cout << averageY << std::endl;
}