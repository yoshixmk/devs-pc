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

public:
	Locus();
	void calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2);
	double getAInclination();
	double getBIntercept();
	CvPoint getFrameOutPoint(int aLineY);
	void setRandom(bool aIsRandoem);
};

}  // namespace Strategy
#endif
