#include "MalletCoordinate.h"
#include "..\Hardware\Serial.h"
namespace Strategy
{

MalletCoordinate::MalletCoordinate()
{
	mColorExtraction.setMalletHSV();

	//1ch画像から、重心計算はできる。
	mColorExtraction.extractRobotSideHockeyTable();
	//cvSetImageCOI(malletMasikingImage, 1); //左は使用できなくなった
	IplImage* malletMasikingImage = mColorExtraction.getSingleColorExtraction();

	CvMoments moment_mallet;
	cvMoments(malletMasikingImage, &moment_mallet, 0);

	double m00_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 0);
	double m10_now_mallet = cvGetSpatialMoment(&moment_mallet, 1, 0);
	double m01_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 1);

	double gX_now_mallet = m10_now_mallet / m00_now_mallet;
	double gY_now_mallet = m01_now_mallet / m00_now_mallet;

	//初期化時は前回の座標と現在の座標は同じ。
	mXYCoordinate = cvPoint(gX_now_mallet, gY_now_mallet);
}

CvPoint MalletCoordinate::getCoordinate()
{
	//1ch画像から、重心計算はできる。
	mColorExtraction.extractRobotSideHockeyTable();
	//cvSetImageCOI(malletMasikingImage, 1); //左は使用できなくなった
	IplImage* malletMasikingImage = mColorExtraction.getSingleColorExtraction();

	CvMoments moment_mallet;
	cvMoments(malletMasikingImage, &moment_mallet, 0);

	double m00_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 0);
	double m10_now_mallet = cvGetSpatialMoment(&moment_mallet, 1, 0);
	double m01_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 1);

	double gX_now_mallet = m10_now_mallet / m00_now_mallet;
	double gY_now_mallet = m01_now_mallet / m00_now_mallet;

	mNowMalletX = (int)gX_now_mallet;
	mNowMalletY = (int)gY_now_mallet;
	CvPoint mXYCoordinate = cvPoint(mNowMalletX, mNowMalletY);

	//serialのバッファも更新する
	renewSerialBuf();

	return mXYCoordinate;
}

void MalletCoordinate::renewSerialBuf()
{
	//7, 8バイト目のみの更新用
	unsigned char buf[8] = {0, 1, 'A', 3, 4, 'B', mNowMalletX/2, mNowMalletY/2};
	
	Hardware::Serial::serialWriteRange((char*)buf, 6, 7);
	cv::waitKey(1);
}

}  // namespace Strategy
