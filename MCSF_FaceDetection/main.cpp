#include "FaceDetection.h"
#include "VideoProcessor.h"

#include "opencv2\opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	/// use opencv mode to detect face for video
	VideoProcessor processor;
	processor.setInput(0);
	//processor.displayInput("current Frame");
	processor.displayOutput("output Frame");
	processor.setDelay(10);

	FaceDetection faceDetection(FaceDetection::OPENCV_CASCADE_CLASSIFIER);
	//faceDetection.loadCascadeXMLPath("haarcascade_frontalface_default.xml");
	faceDetection.loadCascadeXMLPath("haarcascade_profileface.xml");
	processor.setFrameProcessor(&faceDetection);
	processor.run();


	/// use shiqiyu mode to detect face for video
	//VideoProcessor processor;
	//processor.setInput(0);
	////processor.displayInput("current Frame");
	//processor.displayOutput("output Frame");
	//processor.setDelay(1);

	//FaceDetection faceDetection(FaceDetection::SHIQIYU_LIBFACE_DETECTION);
	//processor.setFrameProcessor(&faceDetection);
	//processor.run();


	/// use shiqiyu mode to detect face for images.
	/*FaceDetection faceDetection(FaceDetection::SHIQIYU_LIBFACE_DETECTION);
	cv::Mat input = cv::imread("E:media/face.jpg");
	cv::Mat output;
	faceDetection.process(input, output);
	cv::imshow("Face", output);
	cv::waitKey();
*/

	/// use opencv mode to detect face for images.
	/*cv::Mat input = cv::imread("E:media/face.jpg");
	cv::Mat output;

	FaceDetection pFaceDetection(FaceDetection::OPENCV_CASCADE_CLASSIFIER);
	if (pFaceDetection.loadCascadeXMLPath("haarcascade_frontalface_default.xml"))
	{
		pFaceDetection.process(input, output);
	}
	cv::imshow("Face", output);
	cv::waitKey();*/

	return 0;
}