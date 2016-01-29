#include "FrequencySwitchingX.h"

namespace Strategy 
{

FrequencySwitchingX::FrequencySwitchingX() :FrequencySwitching()
{
	mInitFrequency = 400;
	mFrequencyUpCount = 32;
	mAmountOfChange = 100;
	mIntervaTime = 0.010;
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

//時間内にできるだけ周波数を上げて、最後に周波数を落とす
void FrequencySwitchingX::output()
{	
	double passed_time = mTimer.getOperatingTime();
	char buf[8];
	if (passed_time < mTargetTime - mIntervaTime * mFrequencyUpCount){ //upper and keeping time
		for (int i = 0; i <= mFrequencyUpCount; i++){
			if (passed_time < mIntervaTime * (i + 1)){
				if (mCurrentFrequency != mInitFrequency + mAmountOfChange * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChange * i;
					buf[0] = mCurrentFrequency / 10 / 2;
					Hardware::Serial::changeBuf(buf, 0);
				}
				break;
			}
		}
	}
	else if (passed_time <= mTargetTime){ //downer
		for (int i = mFrequencyUpCount; 0 <= i; i--){
			if (passed_time <= mTargetTime - mIntervaTime * i){
				//現在の周波数 != 初期値 + 減らした周波数
				if (mCurrentFrequency != mInitFrequency + mAmountOfChange * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChange * i;
					buf[0] = mCurrentFrequency / 10 / 2;
					Hardware::Serial::changeBuf(buf, 0);
				}
				break;
			}
		}
	}
	else{
		if (mCurrentFrequency != 0){
			buf[0] = 0;
			Hardware::Serial::changeBuf(buf, 0);
		}
	}
	FrequencySwitching::output();
}

void FrequencySwitchingX::stop(){
	char buf[8];
	buf[0] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	FrequencySwitching::output();
}

int FrequencySwitchingX::getCurrentFrequency(){
	return mCurrentFrequency;
}

} /* namespace Strategy */
