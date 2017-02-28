#ifndef VIDEO_PRCESSOR_H__
#define VIDEO_PRCESSOR_H__

#include "FeatureTracker.h"

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor
{
private:
	cv::VideoCapture _capture;

	void (*_processf)(const cv::Mat& src, cv::Mat& dst);
	FrameProcessor* _frameProcessor;

	bool _callIt;
	std::string _windowNameInput;
	std::string _windowNameOutput;

	int _delay;
	long _fnumber;
	long _frameToStop;
	bool _stop;

public:
	VideoProcessor():_callIt(true), _delay(0), _fnumber(0), _stop(false), _frameToStop(-1){}

	void setDelay(int d);

	void setFrameProcessor(void (*frameProcessCallBack)(const cv::Mat& src, cv::Mat& dst));

	void setFrameProcessor(FrameProcessor* frameProcessorPtr);

	bool setInput(std::string filename);

	bool setInput(int i = 0);

	void displayInput(std::string wn);

	void displayOutput(std::string wn);

	void dontDisplay();

	void run();

	double getFrameRate();

private:
	void stopIt();

	bool readNextFrame(cv::Mat& frame);
	
	double getFrameNumber();
};

#endif