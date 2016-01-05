#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "../Strategy/FrequencySwitching.h"
#include "../Strategy/FrequencySwitchingX.h"
#include "../Strategy/FrequencySwitchingY.h"
#include "../Strategy/FrameCoordinate.h"
//#include "../Strategy/AnomalyDetection.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitchingX mFrequencySwitchingX;
	FrequencySwitchingY mFrequencySwitchingY;
	//AnomalyDetection anomalyDetection;

	void moveForLimit();

	void limitCheck();

public:
	void moveToCenter(CvPoint aMalletCoordinate);

	void moveToHitBack(CvPoint aPredictedCoordinate, CvPoint aMalletCoordinate);
};

}  // namespace Strategy
#endif
