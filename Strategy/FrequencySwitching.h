#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "../Hardware/Timer.h"
#include "../Hardware/Serial.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace Strategy {
class FrequencySwitching {

protected:
	char mTargetDirection; //'A' 'B' 'C' 'D'

	double mTargetTime;
	int mCurrentFrequency;
	int mInitFrequency;

	int mFrequencyUpCount;		//周波数を上げる回数
	int mAmountOfChange;			//周波数変化量(Hz)
	double mIntervaTime;		//時間間隔(s)
	int mMoveDistanceX;
	int mMoveDistanceY;

	int mTimeAjustMentY;

	Hardware::Timer mTimer;
	Hardware::Timer mMovingStopTimer;

public:
	FrequencySwitching();
	~FrequencySwitching();
	void setOutputInformation(char aDirection, double aTime);
	void output();
	void stop();
	int getCurrentFrequency();
	void setFrequencyX(int aFrequency);
	void setFrequencyY(int aFrequency);
	void sankakuProcess(int aMoveDistance);
	void sankakuDefense(int aMoveDistance);
	void sankakuReturnProcess();
	void sankakuUntilHit(int aMoveDistanceX, int aMoveDistanceY);
	void sankakuReturnUntilHit();
	void sankakuRightAngle(int aMoveDistanceX, int aMoveDistanceY);
	//void sankakuReturnRightAngle();
};

}  // namespace Strategy
#endif
