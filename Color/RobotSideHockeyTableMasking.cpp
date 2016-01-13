#include "RobotSideHockeyTableMasking.h"

namespace Color
{

RobotSideHockeyTableMasking::RobotSideHockeyTableMasking() :mTwoImageSynthesis()
{
	mRobotSideHockeyTableImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 4);
}

IplImage* RobotSideHockeyTableMasking::mask()
{
	IplImage* src_img;
	src_img = mTwoImageSynthesis.synthesizeNonDistortion();
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

	pts[1][0] = cvPoint(29, height);
	pts[1][1] = cvPoint(24, 409);
	pts[1][2] = cvPoint(75, 465);
	pts[1][3] = cvPoint(246, 463);
	pts[1][4] = cvPoint(310, 410);
	pts[1][5] = cvPoint(299, height);
//	pts[1][6] = cvPoint(39, 233);
//	pts[1][7] = cvPoint(15, 217);


//    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
	cvCopy(src_img, mRobotSideHockeyTableImage);
//    mRobotSideHockeyTableImage = src_img;
    cvFillPoly(mRobotSideHockeyTableImage, pts, npts, 2, CV_RGB(0, 0, 0));

	return mRobotSideHockeyTableImage;
}
}  // namespace Color
