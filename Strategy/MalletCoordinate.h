#ifndef STRATEGY_MALLET_COORDINATE_H
#define STRATEGY_MALLET_COORDINATE_H

#include "Coordinate.h"
#include "../Hardware/Serial.h"
#include "../CLEye/opencv.hpp"

namespace Strategy
{
class MalletCoordinate : public Coordinate
{
private:
	Hardware::Serial mSerial;
	CvPoint mXYCoordinate;
	int mNowMalletX;
	int mNowMalletY;
	void renewSerialBuf();

public:
	MalletCoordinate();
	CvPoint getCoordinate();
};

}  // namespace Strategy
#endif
