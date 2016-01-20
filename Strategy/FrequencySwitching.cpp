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

void FrequencySwitching::sankakuProcess(char aDirection, int aMoveDistance)
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
	//printf("move_dist: %c\n", aDirection);
	//printf("max_freq: %d\n",max_freq);

	mBuf[0] = nowFrequency / 20;
	mBuf[1] = 500 / 20;
	mBuf[2] = aDirection;
	while(max_freq > nowFrequency){
		mBuf[0] = nowFrequency / 20;
		mBuf[1] = 500 / 20;
		//std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency+100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	while(mInitFrequency <= nowFrequency){
		mBuf[0] = nowFrequency / 20;
		mBuf[1] = 500 / 20;
		//std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency - 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	mBuf[0] = 0;
	mBuf[1] = 0;

	FrequencySwitching::output();
}

}  // namespace Strategy
