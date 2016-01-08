#ifndef STRATEGY_LOCUS_H
#define STRATEGY_LOCUS_H

#include "Coordinate.h"
#include "RandomPositionCoordinate.h"
#include "../CLEye/opencv.hpp"

namespace Strategy {
class Locus {
private:
	double mAInclination;

	double mBIntercept;

	bool mIsRandom;

	Coordinate mPositionalCoordinate;
	RandomPositionCoordinate mRandomPositionCoordinate;

public:
	void calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2);

	double getAInclination();

	double getBIntercept();

};

}  // namespace Strategy
#endif
