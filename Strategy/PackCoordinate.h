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

	CvPoint mPreviousXYCoordinate;

public:
	PackCoordinate();

	CvPoint getCoordinate();

	CvPoint getPreviousCoordinate();

};

}  // namespace Strategy
#endif
