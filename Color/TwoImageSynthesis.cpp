#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis()
{
	mImgRobotSide = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 4);
	mImgHumanSide = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 4);
	mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 4);
}

TwoImageSynthesis::~TwoImageSynthesis()
{
	cvReleaseImage(&mImgRobotSide);
	cvReleaseImage(&mImgHumanSide);
	cvReleaseImage(&mSynthesisImage);
}

IplImage* TwoImageSynthesis::synthesize()
{
	mImgRobotSide = Hardware::Camera::getRobotSideImage();
	mImgHumanSide = Hardware::Camera::getHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(mImgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(mImgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatSynthesisImage);
	IplImage* mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 4);
	*mSynthesisImage = mMatSynthesisImage;

	return mSynthesisImage;
}

IplImage* TwoImageSynthesis::synthesizeNonDistortion()
{
	mImgRobotSide = perspectiveTransformation.transformRobotSideImage();
	mImgHumanSide = perspectiveTransformation.transformHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(mImgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(mImgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatNonDistortionImage);
	*mSynthesisImage = mMatNonDistortionImage;

	return mSynthesisImage;
}

}  // namespace Color

