#ifndef FRAME_PROCESSOR_H__
#define FRAME_PROCESSOR_H__

namespace cv{
	class Mat;
}


class FrameProcessor
{
public:
	virtual void process(const cv::Mat &input, cv::Mat &output) = 0;
};
#endif