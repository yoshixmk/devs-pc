#include "FrequencySwitchingX.h"

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX() :FrequencySwitching()
{
	mInitFrequency = 300;
	mFrequencyUpCount = 32;
	mAmountOfChang = 100;
	mIntervaTime = 0.010;

	for (int i = 0; i < 4; i++){
		FrequencySwitching::mBuf[i] = 0;
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

//ŽžŠÔ“à‚É‚Å‚«‚é‚¾‚¯Žü”g”‚ðã‚°‚ÄAÅŒã‚ÉŽü”g”‚ð—Ž‚Æ‚·
void FrequencySwitchingX::output()
{	
	double passed_time = mTimer.getOperatingTime();

	if (passed_time < mTargetTime - mIntervaTime * mFrequencyUpCount){ //upper and keeping time
		for (int i = 0; i <= mFrequencyUpCount; i++){
			if (passed_time < mIntervaTime * (i + 1)){
				if (mCurrentFrequency != mInitFrequency + mAmountOfChang * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChang * i;
					mBuf[0] = mCurrentFrequency / 10 / 2;
				}
				break;
			}
		}
	}
	else{ //downer
		for (int i = mFrequencyUpCount; 0 <= i; i--){
			if (passed_time <= mTargetTime - mIntervaTime * i){
				//Œ»Ý‚ÌŽü”g” != ‰Šú’l + Œ¸‚ç‚µ‚½Žü”g”
				if (mCurrentFrequency != mInitFrequency + mAmountOfChang * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChang * i;
					mBuf[0] = mCurrentFrequency / 10 / 2;
				}
				break;
			}
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
