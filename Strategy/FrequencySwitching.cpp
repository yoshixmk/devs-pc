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

	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;
	}
}

FrequencySwitching::~FrequencySwitching()
{
}

void FrequencySwitching::setOutputInformation(char aTargetDirection, double aTargetTime)
{
	//方向または時間が変わっていたら、時間をリセットする
	if (mTargetDirection != aTargetDirection){
		mTargetDirection = aTargetDirection;
		mTimer.resetStartOperatingTime();
	}
	if (mTargetTime != aTargetTime){
		mTargetTime = aTargetTime;
		mTimer.resetStartOperatingTime();
	}
	mBuf[2] = mTargetDirection;
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
