#include "PackCoordinate.h"

namespace Strategy
{

PackCoordinate::PackCoordinate()
{
	mColorExtraction.setPackHSV();

	//1ch画像から、重心計算はできる。
	mColorExtraction.extractHockeyTable();
	//cvSetImageCOI(packMasikingImage, 1); //左は使用できなくなった
	IplImage* packMasikingImage = mColorExtraction.getSingleColorExtraction();
	
	CvMoments moment_pack;
	cvMoments(packMasikingImage, &moment_pack, 0);

	double m00_now_pack = cvGetSpatialMoment(&moment_pack, 0, 0);
	double m10_now_pack = cvGetSpatialMoment(&moment_pack, 1, 0);
	double m01_now_pack = cvGetSpatialMoment(&moment_pack, 0, 1);

	double gX_now_pack = m10_now_pack / m00_now_pack;
	double gY_now_pack = m01_now_pack / m00_now_pack;

	//初期化時は前回の座標と現在の座標は同じ。
	mXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
	for(int i=0; i<sizeof(mPreviousXYCoordinate)/sizeof(mPreviousXYCoordinate[0]); i++){
		mPreviousXYCoordinate[i] = cvPoint(gX_now_pack, gY_now_pack);
	}
}

CvPoint PackCoordinate::getCoordinate()
{
	//現在の座標を、前回の座標に変える
	for(int i=sizeof(mPreviousXYCoordinate)/sizeof(mPreviousXYCoordinate[0])-1; i>0; i--){
		mPreviousXYCoordinate[i] = mPreviousXYCoordinate[i-1];
	}
	mPreviousXYCoordinate[0] = mXYCoordinate;
	
	//1ch画像から、重心計算はできる。
	mColorExtraction.extractHockeyTable();

	//cvSetImageCOI(packMasikingImage, 1); //左は使用できなくなった
	IplImage* packMasikingImage = mColorExtraction.getSingleColorExtraction();

	CvMoments moment_pack;
	cvMoments(packMasikingImage, &moment_pack, 0);

	double m00_now_pack = cvGetSpatialMoment(&moment_pack, 0, 0);
	double m10_now_pack = cvGetSpatialMoment(&moment_pack, 1, 0);
	double m01_now_pack = cvGetSpatialMoment(&moment_pack, 0, 1);

	double gX_now_pack = m10_now_pack / m00_now_pack;
	double gY_now_pack = m01_now_pack / m00_now_pack;

	//現在の座標を格納
	mXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
	return mXYCoordinate;
}

CvPoint PackCoordinate::getPreviousCoordinate(int aryNum)
{
	return mPreviousXYCoordinate[aryNum];
}
}  // namespace Strategy
