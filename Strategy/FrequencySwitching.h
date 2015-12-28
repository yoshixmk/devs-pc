﻿#ifndef STRATEGY_FREQUENCY_SWITCHING_H
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

	static char mBuf[4]; //送信する内容

	Hardware::Serial mSerial;
	Hardware::Timer mTimer;
	Hardware::Timer mMovingStopTimer;

public:
	//FrequencySwitching();
	FrequencySwitching();

	~FrequencySwitching();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();

	void setFrequencyX(int aFrequency);

	void setFrequencyY(int aFrequency);
};

}  // namespace Strategy
#endif
