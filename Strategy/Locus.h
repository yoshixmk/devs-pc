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
	CvPoint mForecastPoint;


public:
	Locus();
	CvPoint Locus::getLocusCoordinate();
	bool calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine);
	double getAInclination();
	double getBIntercept();
	CvPoint getFrameOutPoint(int aLineY);
	void setRandom(bool aIsRandoem);
};

}  // namespace Strategy
#endif
