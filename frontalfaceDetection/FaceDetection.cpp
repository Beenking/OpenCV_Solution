#include "FaceDetection.h"
#include "facedetect-dll.h"
#include <vector>
#include <iostream>
#include <string>

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

FaceDetection::FaceDetection(FaceDetectionMode mode)
{
	_faceDetectionMode = mode;
	if (mode == SHIQIYU_LIBFACE_DETECTION)
	{
		//pBuffer is used in the detection functions.
		//If you call functions in multiple threads, please create one buffer for each thread!
		_pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	}
}


FaceDetection::~FaceDetection()
{
	//release the buffer
	free(_pBuffer);
}


void FaceDetection::process(const cv::Mat & input, cv::Mat & output)
{
	input.copyTo(output);
	cv::Mat gray;
	cv::cvtColor(input, gray, CV_BGR2GRAY); //转换成灰度图，因为harr特征从灰度图中提取
	if ( _faceDetectionMode == OPENCV_CASCADE_CLASSIFIER )
	{
		cv::equalizeHist(gray, gray);  //直方图均衡行
		_pccf->detectMultiScale(gray, _faces, 1.3, 13, 0, cv::Size(10, 10), cv::Size(400, 400)); //检测人脸

		for (auto iter = _faces.begin(); iter != _faces.end(); iter++)
		{
			cv::rectangle(output, *iter, cv::Scalar(0, 0, 255), 2, 8); //画出脸部矩形
		}
	}
	else if (_faceDetectionMode == SHIQIYU_LIBFACE_DETECTION)
	{
		// SHIQIYU_LIBFACE_DETECTION
		int doLandmark = 1;
		int *pResults = facedetect_multiview_reinforce(_pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
			1.2f, 3, 48, 0, doLandmark);
		printf("%d faces detected.\n", (pResults ? *pResults : 0));

		//print the detection results
		for (int i = 0; i < (pResults ? *pResults : 0); i++)
		{
			short * p = ((short*)(pResults + 1)) + 142 * i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];
			int neighbors = p[4];
			int angle = p[5];


			printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
			cv::rectangle(output, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 2);
			if (doLandmark)
			{
				for (int j = 0; j < 68; j++)
					cv::circle(output, cv::Point((int)p[6 + 2 * j], (int)p[6 + 2 * j + 1]), 1, cv::Scalar(0, 255, 0));
			}
		}
	}
}

bool FaceDetection::setCascadeXMLPath(const std::string xmlPath)
{
	_pccf = std::make_shared<cv::CascadeClassifier>();
	if (!_pccf->load(xmlPath))
	{
		std::cout << "load xml file failed" << std::endl;
		return false;
	}
	return true;
}
