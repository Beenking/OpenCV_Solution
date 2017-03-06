#ifndef _FEATURE_TRACKER_H__
#define _FEATURE_TRACKER_H__

#include "FrameProcessor.h"
#include <opencv2/opencv.hpp>



class FeatureTracker : public FrameProcessor
{
private:
	cv::Mat _gray_cur;
	cv::Mat _gray_pre;
	std::vector<cv::Point2f> _points[2];

	std::vector<cv::Point2f> _initial;
	std::vector<cv::Point2f> _features;

	// goodFeatureToTrack arguments
	int _max_count;
	double _qlevel;
	double _minDist;

	std::vector<uchar> _status;
	std::vector<float> _err;

public:
	FeatureTracker():_max_count(10), _qlevel(0.01), _minDist(10.){}

	virtual void process(const cv::Mat &input, cv::Mat &output);

private:
	bool needAddNewPoints();

	void detectFeaturePoints();

	bool acceptTrackedPoint(int i);

	void handleTrackedPoints(cv::Mat& output);
};

#endif