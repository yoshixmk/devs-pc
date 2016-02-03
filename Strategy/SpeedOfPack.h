#ifndef SPEED_OF_PACK_H
#define SPEED_OF_PACK_H

#include "PackCoordinate.h"

#include <math.h>

namespace Strategy
{
class SpeedOfPack
{
private:
	//PackCoordinate mPackCoordinate;
	
	//移動平均を使用する
	double mSpeed[10];

public:
	SpeedOfPack();
	double getSpeed();
};

}  // namespace Strategy
#endif
