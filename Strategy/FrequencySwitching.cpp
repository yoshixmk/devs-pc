#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching()
{
	mCurrentFrequency = 0;
	mTargetTime = 0;
	mTargetDirection = 'A';
	mTargetTime = 0;

	char buf[8];
	for (int i = 0; i < 8; i++){
		buf[i] = 0;
	}
	buf[2] = 'A';
	buf[5] = 'A';
	for (int i = 0; i < 8; i++){
		Hardware::Serial::changeBuf(buf, i);
	}

	mInitFrequency = 400;
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
	char buf[8];
	buf[2] = mTargetDirection;
	Hardware::Serial::changeBuf(buf, 2);
}

void FrequencySwitching::output()
{
	Hardware::Serial::serialWrite();
}

void FrequencySwitching::stop()
{
	char buf[8];
	buf[0] = 0;
	buf[1] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 1);
	Hardware::Serial::serialWrite();
}

void FrequencySwitching::setFrequencyX(int aFrequency){
	char buf[8];
	buf[0] = aFrequency;
	Hardware::Serial::changeBuf(buf, 0);
	//Hardware::Serial::serialWrite();
}

void FrequencySwitching::setFrequencyY(int aFrequency){
	char buf[8];
	buf[1] = aFrequency;
	Hardware::Serial::changeBuf(buf, 1);
}

void FrequencySwitching::sankakuProcess(int aMoveDistance)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50; //100
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistance);
	mMoveDistance = aMoveDistance;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.22*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	
	//printf("move_dist: %c\n", aDirection);
	//printf("max_freq: %d\n",max_freq);

	char buf[8];
	buf[0] = nowFrequency / 20;
	Hardware::Serial::changeBuf(buf, 0);
	buf[1] = 500 / 20;
	Hardware::Serial::changeBuf(buf, 1);

	if(aMoveDistance > 0){
		buf[2] = 'B';
	}
	else{
		buf[2] = 'A';
	}
	Hardware::Serial::changeBuf(buf, 2);
	FrequencySwitching::output();

	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 0);
		Hardware::Serial::changeBuf(buf, 1);
		//std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency + 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 0);
		Hardware::Serial::changeBuf(buf, 1);
		//std::cout << "output: " << nowFrequency << std::endl;
		nowFrequency = nowFrequency - 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	buf[0] = 0;
	buf[1] = 0;
	if(aMoveDistance > 0){
		buf[2] = 'D';
	}
	else{
		buf[2] = 'C';
	}
	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 1);
	Hardware::Serial::changeBuf(buf, 2);
	FrequencySwitching::output();
}

void FrequencySwitching::sankakuReturnProcess()
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50;
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(mMoveDistance);

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.22*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	

	char buf[8];
	buf[0] = nowFrequency / 20;
	Hardware::Serial::changeBuf(buf, 0);
	buf[1] = 500 / 20;
	Hardware::Serial::changeBuf(buf, 1);

	if(mMoveDistance > 0){
		buf[2] = 'D';
	}
	else{
		buf[2] = 'C';
	}
	Hardware::Serial::changeBuf(buf, 2);
	FrequencySwitching::output();

	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 0);
		Hardware::Serial::changeBuf(buf, 1);
		nowFrequency = nowFrequency + 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 0);
		Hardware::Serial::changeBuf(buf, 1);
		nowFrequency = nowFrequency - 100;
		Sleep(10);	//10ms
		FrequencySwitching::output();
	}
	buf[0] = 0;
	buf[1] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 1);
	FrequencySwitching::output();
}

}  // namespace Strategy
