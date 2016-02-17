#include "NonFlipTwoImageSynthesis.h"

namespace Color
{
IplImage* NonFlipTwoImageSynthesis::synthesize()
{
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(Hardware::Camera::getRobotSideImage());
	matFrameHumanSide = cv::cvarrToMat(Hardware::Camera::getHumanSideImage());
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatSynthesisImage);
	*mSynthesisImage = mMatSynthesisImage;

	return mSynthesisImage;
}

IplImage* NonFlipTwoImageSynthesis::synthesizeNonDistortion()
{
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(Hardware::Camera::getRobotSideImage());
	matFrameHumanSide = cv::cvarrToMat(Hardware::Camera::getHumanSideImage());
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatNonDistortionImage);
	*mSynthesisImage = mMatNonDistortionImage;

	return mSynthesisImage;
}

}  // namespace Color
