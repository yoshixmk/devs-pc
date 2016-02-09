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
	void moveToCenterDefence(CvPoint aMalletCoordinate);
	void moveToRightCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint);
	void moveToLeftCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint);
	void moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition);
	void DefenceToMove(CvPoint aMalletCoordinate, CvPoint aWaitingPosition, CvPoint forecastPoint);		//defence—p
	bool moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuDefence(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void sankakuCenterBack();
	void sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
	void sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate,CvPoint forecastPoint);
	//void hogehoge(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate);
	void alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate);
	void alarmHitBackDefence(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate);
	void moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate);
};
}  // namespace Strategy
#endif
