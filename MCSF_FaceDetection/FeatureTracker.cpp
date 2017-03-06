#include "FeatureTracker.h"

void FeatureTracker::process(const cv::Mat &input, cv::Mat &output)
{
	cv::cvtColor(input, _gray_cur, CV_BGR2GRAY);
	input.copyTo(output);

	// 1. 如果需要添加新的特征点
	if(needAddNewPoints())
	{
		detectFeaturePoints();
		_points[0].insert(_points[0].end(), _features.begin(), _features.end());
		_initial.insert(_initial.end(), _features.begin(), _features.end());
	}

	if(_gray_pre.empty())
	{
		_gray_cur.copyTo(_gray_pre);
	}

	// 2.1 跟踪特征点
	if(_points[0].size() == 0)
	{
		std::cout << "no good features detected" << std::endl;
		return;
	}
	cv::calcOpticalFlowPyrLK(_gray_pre,
							_gray_cur,
							_points[0],
							_points[1], // output
							_status, // output
							_err);   // output

	// 2.2 遍历所有跟踪的点进行筛选
	int k = 0;
	for(int i = 0; i < _points[1].size(); ++i)
	{
		if(acceptTrackedPoint(i))
		{
			_initial[k] = _initial[i];
			_points[1][k++] = _points[1][i];
		}
	}
	_points[1].resize(k);
	_initial.resize(k);

	handleTrackedPoints(output);
	std::swap(_points[1], _points[0]);
	cv::swap(_gray_pre, _gray_cur);
}

bool FeatureTracker::needAddNewPoints()
{
	return _points[0].size() <= 10;
}

void FeatureTracker::detectFeaturePoints()
{
	cv::goodFeaturesToTrack(_gray_cur,
							_features,
							_max_count,
							_qlevel,
							_minDist);
}

bool FeatureTracker::acceptTrackedPoint(int i)
{
	return _status[i] && 
		   (abs(_points[0][i].x - _points[1][i].x) + 
		   abs(_points[0][i].y - _points[1][i].y) > 2);
}

void FeatureTracker::handleTrackedPoints(cv::Mat& output)
{
	for(int i = 0; i < _points[1].size(); ++i)
	{
		cv::line(output,
				 _initial[i],
				 _points[1][i],
				 cv::Scalar(255,255,255));
		cv::circle(output, _points[1][i], 3, cv::Scalar(255,255,255), -1);
	}
}