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
	Hardware::Serial serial;
	//char buf[8] = {0, 1, 'A', 3, 4, 5,(int)gX_now_mallet/2,(int)gY_now_mallet/2};
	////serial.setWriteRange(buf, 6, 7);

	//serial.serialWrite((char*)buf, 8);
	//if (buf[2] == 'A'){
	//			buf[2] = 'B';
	//}
	//else if (buf[2] == 'B'){
	//			buf[2] = 'A';
	//}
	CvPoint mXYCoordinate = cvPoint(gX_now_mallet, gY_now_mallet);
	return mXYCoordinate;
}
}  // namespace Strategy
