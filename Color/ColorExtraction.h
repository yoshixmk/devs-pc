#ifndef COLOR_COLOR_EXTRACTION_H
#define COLOR_COLOR_EXTRACTION_H

#include "HockeyTableMasking.h"
#include "RobotSideHockeyTableMasking.h"
#include "../Hardware/Camera.h"
#include "../CLEye/opencv.hpp"

namespace Color
{
class ColorExtraction
{
private:
	int mHMin;
	int mHMax;
	int mSMin;
	int mSMax;
	int mVMin;
	int mVMax;
	Color::HockeyTableMasking mHockeyTableMasking;
	Color::RobotSideHockeyTableMasking mRobotSideHockeyTableMasking;
	void cvColorExtraction(IplImage* aSrcImg, IplImage* aDstImg,
						   int aCode,
						   int aCh1Lower, int aCh1Upper,
						   int aCh2Lower, int aCh2Upper,
						   int aCh3Lower, int aCh3Upper);
	IplImage* mColorExtractionImage;
	IplImage* mSrc3Ch;
	IplImage* mSingleColorImage;

public:
	ColorExtraction();
	ColorExtraction(int aHMin, int aHMax, int aSMin, int aSMax, int aVMin, int aVMax);
	~ColorExtraction();
	void setHSV(int aHMin, int aHMax, int aSMin, int aSMax, int aVMin, int aVMax);
	IplImage* extractHockeyTable();
	IplImage* extractRobotSideHockeyTable();
	void setMalletHSV();
	void setPackHSV();
	IplImage* getSingleColorExtraction();
};

}  // namespace Color
#endif
