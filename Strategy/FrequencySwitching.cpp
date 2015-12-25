#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching(char aXaxisOrYaxis)
{
	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 0;
	mNowDirection = 'R';
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
	mTargetDirection = aTargetDirection;
	mTargetTime = aTargetTime;
	mTimer.resetStartOperatingTime();
}

void FrequencySwitching::output()
{
}

void FrequencySwitching::stop()
{
	
}

}  // namespace Strategy
