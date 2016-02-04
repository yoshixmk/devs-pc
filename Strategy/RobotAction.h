#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "../Strategy/FrequencySwitching.h"
#include "../Strategy/FrameCoordinate.h"
#include "../Strategy/FrequencyManualX.h"
#include "../Strategy/FrequencyManualY.h"
#include "../Strategy/SpeedOfPack.h"
#include "../Hardware/Timer.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitching mFrequencySwitching;
	FrequencyManualX mFrequencyManualX;
	FrequencyManualX mCenterFrequencyManualX;
	FrequencyManualY mFrequencyManualY;

protected:
	FrequencyManual mFrequencyManual;
	SpeedOfPack mSpeedOfPack;
	Hardware::Timer mMoveingTimer;
	Hardware::Timer mAlarmTimer;
	void moveForLimit();
	void limitCheck();

public:
	void moveToCenter(CvPoint aMalletCoordinate);
	void moveToRightCenter(CvPoint aMalletCoordinate);
	void moveToLeftCenter(CvPoint aMalletCoordinate);
	void moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition);
	bool moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuCenterBack();
	void sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
	void sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
	void alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate);
	void moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
};
}  // namespace Strategy
#endif
