#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "../Strategy/FrequencySwitching.h"
//#include "../Strategy/FrequencySwitchingX.h"
//#include "../Strategy/FrequencySwitchingY.h"
#include "../Strategy/FrameCoordinate.h"
#include "../Strategy/FrequencyManualX.h"
#include "../Strategy/FrequencyManualY.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitching mFrequencySwitching;
	FrequencyManual mFrequencyManual;
	FrequencyManualX mFrequencyManualX;
	FrequencyManualY mFrequencyManualY;
	void moveForLimit();
	void limitCheck();

public:
	void moveToCenter(CvPoint aMalletCoordinate);
	bool moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
};

}  // namespace Strategy
#endif
