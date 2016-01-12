#ifndef SPEED_OF_PACK_H
#define SPEED_OF_PACK_H

#include "PackCoordinate.h"

namespace Strategy
{
class SpeedOfPack
{
private:
	PackCoordinate packCoordinate;
	int mSpeed;

public:
	SpeedOfPack(void);
	~SpeedOfPack(void);

	int getSpeed();
};

}  // namespace Strategy
#endif
