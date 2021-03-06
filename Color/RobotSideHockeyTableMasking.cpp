#include "RobotSideHockeyTableMasking.h"

namespace Color
{

RobotSideHockeyTableMasking::RobotSideHockeyTableMasking() :mTwoImageSynthesis()
{
	mRobotSideHockeyTableImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 4);
}

RobotSideHockeyTableMasking::~RobotSideHockeyTableMasking()
{
	cvReleaseImage(&mRobotSideHockeyTableImage);
}

IplImage* RobotSideHockeyTableMasking::mask()
{
	IplImage* src_img = mTwoImageSynthesis.synthesizeNonDistortion();
	int width = Hardware::Camera::getWidth();
	int height = Hardware::Camera::getHeight();

	int npts[2] = { 4, 6 };
	CvPoint **pts;
//	CvPoint center_frame_left = cvPoint(11, height);
//	CvPoint center_frame_right = cvPoint(155, height);

	pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 6);
	pts[0][0] = cvPoint(0,0);
	pts[0][1] = cvPoint(width,0);
	pts[0][2] = cvPoint(width, height*2);
	pts[0][3] = cvPoint(0, height*2);

	//マレットの見える範囲のみ
	pts[1][0] = cvPoint(35, height+60);
	pts[1][1] = cvPoint(33, 398);
	pts[1][2] = cvPoint(83, 450);//441
	pts[1][3] = cvPoint(233, 455);//448
	pts[1][4] = cvPoint(290, 410);
	pts[1][5] = cvPoint(297, height+60);

	cvCopy(src_img, mRobotSideHockeyTableImage);
    cvFillPoly(mRobotSideHockeyTableImage, pts, npts, 2, CV_RGB(0, 0, 0));

	return mRobotSideHockeyTableImage;
}

//更新なしで取得。更新＆取得は、mask()を呼び出し。
IplImage* RobotSideHockeyTableMasking::getMaskingImage()
{
	return mRobotSideHockeyTableImage;
}
}  // namespace Color
