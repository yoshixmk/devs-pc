#include "FrequencySwitchingX.h"

namespace Strategy {

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

	if (passed_time < mTargetTime - mIntervaTime * mFrequencyUpCount){ //upper and keeping time
		for (int i = 0; i <= mFrequencyUpCount; i++){
			if (passed_time < mIntervaTime * (i + 1)){
				if (mCurrentFrequency != mInitFrequency + mAmountOfChange * i){
					mCurrentFrequency = mInitFrequency + mAmountOfChange * i;
					mBuf[0] = mCurrentFrequency / 10 / 2;
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
					mBuf[0] = mCurrentFrequency / 10 / 2;
				}
				break;
			}
		}
	}
	else{
		if (mCurrentFrequency != 0){
			mBuf[0] = 0;
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

void FrequencySwitchingX::sankakuProcess(char aDistination, int aMoveDistance)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 100;
	int freq =0;
	int nowFrequency = mInitFrequency;
	
	while(aMoveDistance >= next_freq * 2){
		next_freq = next_freq + sum +0.10*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	
	printf("move_dist: %c\n", aDistination);
	printf("max_freq: %d\n",max_freq);

	mBuf[1] = nowFrequency / 20;
	mBuf[2] = aDistination;
	while(max_freq > nowFrequency){
		mBuf[0] = nowFrequency / 20;
		std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency+100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	while(mInitFrequency <= nowFrequency){
		mBuf[0] = nowFrequency / 20;
		std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency - 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	mBuf[0] = 0;

	FrequencySwitching::output();
}

} /* namespace Strategy */
