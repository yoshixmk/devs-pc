#ifndef STRATEGY_LOCUS_H
#define STRATEGY_LOCUS_H

#include "Coordinate.h"
#include "RandomPositionCoordinate.h"
#include "FrameCoordinate.h"
#include "../CLEye/opencv.hpp"

namespace Strategy {
class Locus {
private:
	double mAInclination;
	double mBIntercept;
	bool mIsRandom;
	//CvPoint mCoordinate1;
	//CvPoint mCoordinate2;

public:
	Locus();
	CvPoint Locus::getLocusCoordinate(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine);
	void calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2);
	double getAInclination();
	double getBIntercept();
	CvPoint getFrameOutPoint(int aLineY);
	void setRandom(bool aIsRandoem);
	void setNextAB();
	//void oldLocus(IplImage* show_img);
};

}  // namespace Strategy
#endif
