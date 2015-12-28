#include "FrequencySwitchingX.h"

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX() :FrequencySwitching()
{
	for (int i = 0; i < 4; i++){
		FrequencySwitching::mBuf[i] = 0;//500 / 10 /2
	}
	mTargetDirection = 'A';
	mTargetTime = 0;
	mCurrentFrequency = 0;
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

void FrequencySwitchingX::output()
{
	for (int i = 0; i <= mFrequencyUpCount; i++){
		if (mTimer.getOperatingTime() < 0.010 * (i+1)){
			if (mBuf[0] != (300 + mAmountOfChang * i) /10 / 2){
				mBuf[0] = (300 + mAmountOfChang * i) / 10 / 2;
			}
			break;
		}
	}
	FrequencySwitching::output();
}

void FrequencySwitchingX::stop(){
	mBuf[0] = 0;
	FrequencySwitching::output();
}

int FrequencySwitchingX::getCurrentFrequency(){
	return mCurrentFrequency;
}

} /* namespace Strategy */
