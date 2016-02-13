#include "FrequencySwitchingWeakX.h"

namespace Strategy {

FrequencySwitchingWeakX::FrequencySwitchingWeakX() :FrequencySwitchingX()
{
	mInitFrequency = 500;
	mFrequencyUpCount = 20;
	mAmountOfChange = 50;
	mIntervaTime = 0.010;

}

FrequencySwitchingWeakX::~FrequencySwitchingWeakX()
{
}

void FrequencySwitchingWeakX::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

void FrequencySwitchingWeakX::output()
{
	double passed_time = mTimer.getOperatingTime();
	char buf[8];
	if (passed_time < mTargetTime - mIntervaTime * mFrequencyUpCount){ //upper and keeping time
		for (int i = 0; i <= mFrequencyUpCount; i++){
			if (passed_time < mIntervaTime * (i + 1)){
				if (mCurrentFrequency != mInitFrequency + mAmountOfChange * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChange * i;
					buf[3] = mCurrentFrequency / 10 / 2;
					Hardware::Serial::changeBuf(buf, 3);
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
					buf[3] = mCurrentFrequency / 10 / 2;
					Hardware::Serial::changeBuf(buf, 3);
				}
				break;
			}
		}
	}
	else{
		if (mCurrentFrequency != 0){
			buf[3] = 0;
			Hardware::Serial::changeBuf(buf, 3);
		}
	}
	FrequencySwitching::output();
}

//時間内にできるだけ周波数を上げて、最後に周波数を落とす
void FrequencySwitchingWeakX::stop()
{
	char buf[8];
	buf[3] = 0;
	Hardware::Serial::changeBuf(buf, 3);
	FrequencySwitching::output();
}

int FrequencySwitchingWeakX::getCurrentFrequency()
{
	return mCurrentFrequency;
}

} /* namespace Strategy */
