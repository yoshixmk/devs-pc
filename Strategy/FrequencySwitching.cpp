#include "FrequencySwitching.h"

namespace Strategy
{
char FrequencySwitching::mBuf[4];

FrequencySwitching::FrequencySwitching()
{
	mCurrentFrequency = 0;
	mTargetTime = 0;
	mTargetDirection = 'A';
	mTargetTime = 0;
	mTimer.resetStartOperatingTime();
}

FrequencySwitching::~FrequencySwitching()
{
}

void FrequencySwitching::setOutputInformation(char aTargetDirection, double aTargetTime)
{
	if (mTargetDirection != aTargetDirection){
		mTargetDirection = aTargetDirection;
	}
	if (mTargetTime != aTargetTime){
		mTargetTime = aTargetTime;
	}
	mTimer.resetStartOperatingTime();
}

void FrequencySwitching::output()
{
	mSerial.serialWrite(mBuf, 4);
}

void FrequencySwitching::stop()
{
	mBuf[0] = 0;
	mBuf[1] = 0;
}

void FrequencySwitching::setFrequencyX(int aFrequency){
	mBuf[0] = aFrequency;
}

void FrequencySwitching::setFrequencyY(int aFrequency){
	mBuf[1] = aFrequency;
}

}  // namespace Strategy
