#pragma once
#ifndef FACE_DETECION_H__
#define FACE_DETECION_H__

#include "FrameProcessor.h" 
#include <memory>
#include <opencv2/opencv.hpp>

class FaceDetection : public FrameProcessor
{
public:
	enum FaceDetectionMode{
		OPENCV_CASCADE_CLASSIFIER = 0,
		// see detail website: https://github.com/ShiqiYu/libfacedetection
		SHIQIYU_LIBFACE_DETECTION 
	};
public:
	FaceDetection(FaceDetectionMode mode = OPENCV_CASCADE_CLASSIFIER);

	~FaceDetection();

	virtual void process(const cv::Mat &input, cv::Mat &output);

	// must use before mode opencv 
	bool loadCascadeXMLPath(const std::string &xmlPath);

private:
	// OPENCV_CASCADE_CLASSIFIER
	FaceDetectionMode _faceDetectionMode;
	std::shared_ptr<cv::CascadeClassifier> _pccf;   //��������������
	std::vector<cv::Rect> _faces;  //����һ�������������������

	// SHIQIYU_LIBFACE_DETECTION
	unsigned char * _pBuffer = nullptr;
};

#endif // !FACE_DETECION_H__
