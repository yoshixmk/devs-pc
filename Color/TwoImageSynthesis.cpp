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

	//開放すると一定時間後停止する
	//cvReleaseImage(&mSynthesisImage);
}

IplImage* TwoImageSynthesis::synthesize()
{
	cvCopy(Hardware::Camera::getRobotSideImage(), mImgRobotSide);
	cvCopy(Hardware::Camera::getHumanSideImage(), mImgHumanSide);
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(mImgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(mImgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatSynthesisImage);
	*mSynthesisImage = mMatSynthesisImage;

	return mSynthesisImage;
}

IplImage* TwoImageSynthesis::synthesizeNonDistortion()
{
	cvCopy(perspectiveTransformation.transformRobotSideImage(), mImgRobotSide);
	cvCopy(perspectiveTransformation.transformHumanSideImage(), mImgHumanSide);
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

