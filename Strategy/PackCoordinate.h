#ifndef STRATEGY_PACK_COORDINATE_H
#define STRATEGY_PACK_COORDINATE_H

#include "Coordinate.h"
#include "../CLEye/opencv.hpp"

namespace Strategy
{
class PackCoordinate : public Coordinate
{
private:
	CvPoint mXYCoordinate;

	CvPoint mPreviousXYCoordinate[10];

public:
	PackCoordinate();

	CvPoint getCoordinate();

	CvPoint getPreviousCoordinate(int aryNum=0);
};

}  // namespace Strategy
#endif
