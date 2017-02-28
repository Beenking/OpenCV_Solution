#include "VideoProcessor.h"

#include <time.h>

void VideoProcessor::setFrameProcessor(void (*frameProcessCallBack)(const cv::Mat&, cv::Mat&))
{
	_frameProcessor = nullptr;
	_processf = frameProcessCallBack;
}

void VideoProcessor::setFrameProcessor(FrameProcessor* frameProcessorPtr)
{
	_processf = nullptr;
	_frameProcessor = frameProcessorPtr;

}

bool VideoProcessor::setInput(std::string filename)
{
	_fnumber = 0;
	_capture.release();
	//images.clear();
	return _capture.open(filename);
}

bool VideoProcessor::setInput(int i)
{
	_fnumber = 0;
	_capture.release();
	//images.clear();
	return _capture.open(i);
}

void VideoProcessor::displayInput(std::string wn)
{
	_windowNameInput = wn;
	cv::namedWindow(_windowNameInput);
}

void VideoProcessor::displayOutput(std::string wn)
{
	_windowNameOutput = wn;
	cv::namedWindow(_windowNameOutput);
}

void VideoProcessor::dontDisplay()
{
	cv::destroyWindow(_windowNameInput);
	cv::destroyWindow(_windowNameOutput);
	_windowNameInput.clear();
	_windowNameOutput.clear();
}

double VideoProcessor::getFrameRate()
{
	return _capture.get(CV_CAP_PROP_FPS);
}

void VideoProcessor::run()
{
	// current src frame
	cv::Mat frame;
	// output processed frame
	cv::Mat output;
	if(!_capture.isOpened())
		return;
	_stop = false;

	while(! _stop)
	{
		if(!readNextFrame(frame))
			break;
		if(_windowNameInput.length() != 0)
			cv::imshow(_windowNameInput, frame);
		if(_windowNameOutput.length() != 0)
			cv::imshow(_windowNameOutput, frame);

		if(_callIt)
		{
			//////////////////////////////////////////////////////
			//clock_t start = clock();
			if(_processf)
				_processf(frame, output);
			else if(_frameProcessor)
				_frameProcessor->process(frame, output);
			//clock_t finish = clock();
			//double totalTime = (finish - start);
			// std::cout << "Process Time Per Frame : " << totalTime << "ms" << std::endl;

			/////////////////////////////////////////////////////

			_fnumber++;
		}
		else
		{
			output = frame;
		}

		if(_windowNameOutput.length() != 0)
		{
			cv::imshow(_windowNameOutput, output);
		}

		if(_delay>=0 && cv::waitKey(_delay)>=0)

			stopIt();
		if(_frameToStop >=0 && getFrameNumber() == _frameToStop)
			stopIt();
	}
}

void VideoProcessor::stopIt()
{
	_stop = true;
}

bool VideoProcessor::readNextFrame(cv::Mat& frame)
{
	return _capture.read(frame);
}

void VideoProcessor::setDelay(int d)
{
	_delay = d;
}

double VideoProcessor::getFrameNumber()
{
	return _fnumber;
}