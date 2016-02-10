#ifndef STRATEGY_ROBOT_ACTION_WEAK_H
#define STRATEGY_ROBOT_ACTION_WEAK_H

#include "RobotAction.h"
#include "../Strategy/FrequencySwitchingWeak.h"
#include "../Strategy/FrequencyManualWeakX.h"
#include "../Strategy/FrequencyManualWeakY.h"

namespace Strategy {
class RobotActionWeak : public RobotAction
{
private:
	FrequencySwitchingWeak mFrequencySwitching;
	FrequencyManualWeakX mFrequencyManualX;
	FrequencyManualWeakX mCenterFrequencyManualX;
	FrequencyManualWeakY mFrequencyManualY;
	int mCenterYLine;

public:
	RobotActionWeak();
	void moveToCenter(CvPoint aMalletCoordinate);
	void moveToCenterDefense(CvPoint aMalletCoordinate);
	void guardCenter(CvPoint aMalletCoordinate);
	void moveToRightCenter(CvPoint aMalletCoordinate);
	void moveToRightCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint);
	void moveToLeftCenter(CvPoint aMalletCoordinate);
	void moveToLeftCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint);
	void moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition);
	bool moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuDefense(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuCenterBack();
	void sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
	void sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
	void alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate);
	void alarmHitBackDefence(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate);
	void moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
};
}  // namespace Strategy
#endif
