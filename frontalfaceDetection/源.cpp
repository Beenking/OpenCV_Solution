#include "FaceDetection.h"
#include "CircleDetector.h"
#include "VideoProcessor.h"

#include "opencv2\opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	VideoProcessor processor;
	processor.setInput(0);
	//processor.displayInput("current Frame");
	processor.displayOutput("output Frame");
	processor.setDelay(1);

	FaceDetection faceDetection(FaceDetection::SHIQIYU_LIBFACE_DETECTION);
	//faceDetection.setCascadeXMLPath("haarcascade_frontalface_default.xml");
	//faceDetection.setCascadeXMLPath("haarcascade_profileface.xml");
	
	processor.setFrameProcessor(&faceDetection);
	processor.run();

	return 0;
}