#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "../Hardware/Timer.h"
#include "../Hardware/Serial.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace Strategy {
class FrequencySwitching {
private:
	char mXaxisOrYaxis;

protected:
	char mNowDirection;
	double mTargetTime;
	int mCurrentFrequency;
	char mTargetDirection;//X: 'L' or 'R' | Y: 'U' or 'D'
	int mFrequency;
	int mFrequencyIndex;
	Hardware::Serial mSerial;
	Hardware::Timer mTimer;
	Hardware::Timer mMovingStopTimer;

public:
	//FrequencySwitching();
	FrequencySwitching(char aXaxisOrYaxis);

	~FrequencySwitching();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();
};

}  // namespace Strategy
#endif
