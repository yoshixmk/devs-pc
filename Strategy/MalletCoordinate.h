#ifndef STRATEGY_MALLET_COORDINATE_H
#define STRATEGY_MALLET_COORDINATE_H

#include "Coordinate.h"
#include "../CLEye/opencv.hpp"

namespace Strategy
{
class MalletCoordinate : public Coordinate
{
private:
	CvPoint mXYCoordinate;

public:
	MalletCoordinate();
	CvPoint getCoordinate();

};

}  // namespace Strategy
#endif
