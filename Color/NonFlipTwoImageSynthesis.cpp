#include "NonFlipTwoImageSynthesis.h"

namespace Color
{
NonFlipTwoImageSynthesis::NonFlipTwoImageSynthesis() : TwoImageSynthesis()
{
	mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 4);
}

IplImage* NonFlipTwoImageSynthesis::synthesize()
{
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(Hardware::Camera::getRobotSideImage());
	matFrameHumanSide = cv::cvarrToMat(Hardware::Camera::getHumanSideImage());
	vconcat(matFrameHumanSide, matFrameRobotSide, mNonFlipTwoImageSynthesisImage);
	*mSynthesisImage = mNonFlipTwoImageSynthesisImage;

	return mSynthesisImage;
}

IplImage* NonFlipTwoImageSynthesis::synthesizeNonDistortion()
{
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(Hardware::Camera::getRobotSideImage());
	matFrameHumanSide = cv::cvarrToMat(Hardware::Camera::getHumanSideImage());
	vconcat(matFrameHumanSide, matFrameRobotSide, mNonFlipTwoImageSynthesisImage);
	*mSynthesisImage = mNonFlipTwoImageSynthesisImage;

	return mSynthesisImage;
}

}  // namespace Color
