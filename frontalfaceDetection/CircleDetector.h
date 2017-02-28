#ifndef CIRCLE_DETECTOR_H__
#define  CIRCLE_DETECTOR_H__


#include "FrameProcessor.h"
#include <vector>
#include <opencv2/opencv.hpp>

class CircleDetector : public FrameProcessor
{
private:
	std::vector<float> _circleCenterPointsY;
	cv::Point2f _point_cur;
public:
	virtual void process(const cv::Mat &input, cv::Mat &output);
};

#endif