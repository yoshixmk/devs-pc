#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching()
{
	mCurrentFrequency = 0;
	mTargetTime = 0;
	mTargetDirection = 'A';
	mTargetTime = 0;

	mTimeAjustMentY = 3;
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
	Hardware::Serial::changeBufRange(buf, 0, 1);
	Hardware::Serial::serialWrite();
}

void FrequencySwitching::setFrequencyX(int aFrequency){
	char buf[8];
	buf[0] = aFrequency;
	Hardware::Serial::changeBuf(buf, 0);
}

void FrequencySwitching::setFrequencyY(int aFrequency){
	char buf[8];
	buf[1] = aFrequency;
	Hardware::Serial::changeBuf(buf, 1);
}

void FrequencySwitching::sankakuDefence(int aMoveDistance)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50; //100
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistance);
	int yTargetCount = 30;
	int yCount = 0;
	mMoveDistanceX = aMoveDistance;
	mMoveDistanceY = 0;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;

	char buf[8];
	buf[0] = nowFrequency / 20;
	buf[1] = 0;
	if(aMoveDistance > 0){
		buf[2] = 'B';
	}
	else{
		buf[2] = 'A';
	}
	
	
	buf[0]=0;
	Hardware::Serial::changeBufRange(buf, 0, 2);
	Sleep(10);
	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		//buf[1] = 500 / 20;
		//マルチタスクで更新タイミング考慮のため、全て更新
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		//buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	buf[0] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	/*for(;yCount < yTargetCount; yCount++){
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 1);
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}*/
	buf[0] = 0;
	buf[1] = 0;
	Hardware::Serial::changeBufRange(buf, 0, 2);
	FrequencySwitching::output();
	Sleep(10);
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
	int yTargetCount = 30;
	int yCount = 0;
	mMoveDistanceX = aMoveDistance;
	mMoveDistanceY = 0;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;

	char buf[8];
	buf[0] = nowFrequency / 20;
	buf[1] = 500 / 20;
	if(aMoveDistance > 0){
		buf[2] = 'B';
	}
	else{
		buf[2] = 'A';
	}
	Hardware::Serial::changeBufRange(buf, 0, 2);

	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		//マルチタスクで更新タイミング考慮のため、全て更新
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	buf[0] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	for(;yCount < yTargetCount; yCount++){
		buf[1] = 500 / 20;
		Hardware::Serial::changeBuf(buf, 1);
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	buf[0] = 0;
	buf[1] = 0;
	Hardware::Serial::changeBufRange(buf, 0, 2);
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
	int moveDistanceAbs = abs(mMoveDistanceX);
	int yTargetCount = 60;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	

	char buf[8];
	buf[0] = nowFrequency / 20;
	buf[1] = 500 / 20;
	if(mMoveDistanceX > 0){
		buf[2] = 'D';
	}
	else{
		buf[2] = 'C';
	}
	Hardware::Serial::changeBufRange(buf, 0, 2);

	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	buf[0] = 0;
	buf[1] = 0;
	Hardware::Serial::changeBufRange(buf, 0, 2);
	FrequencySwitching::output();
}

void FrequencySwitching::sankakuUntilHit(int aMoveDistanceX, int aMoveDistanceY)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50;
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistanceX);
	mMoveDistanceX = aMoveDistanceX;
	mMoveDistanceY = aMoveDistanceY;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	

	char buf[8];
	buf[0] = nowFrequency / 20;
	Hardware::Serial::changeBuf(buf, 0);
	buf[1] = 500 / 20;
	Hardware::Serial::changeBuf(buf, 1);

	if(aMoveDistanceX > 0){
		buf[2] = 'B';
	}
	else{
		buf[2] = 'A';
	}
	Hardware::Serial::changeBufRange(buf, 0, 2);

	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	while(mInitFrequency <= nowFrequency){
		buf[0] = nowFrequency / 20;
		buf[1] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	buf[0] = 0;
	Hardware::Serial::changeBuf(buf, 0);
	FrequencySwitching::output();
	for(int i=0; i<aMoveDistanceY/mTimeAjustMentY; i++){ //Yの距離から時間の変換
		buf[1] = (500 + i*100) / 20;
		Hardware::Serial::changeBufRange(buf, 0, 2);
		FrequencySwitching::output();
		Sleep(10);
	}
	buf[1] = 0;
	Hardware::Serial::changeBuf(buf, 1);
	FrequencySwitching::output();
}

void FrequencySwitching::sankakuRightAngle(int aMoveDistanceX, int aMoveDistanceY)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50;
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistanceX);
	mMoveDistanceX = aMoveDistanceX;
	mMoveDistanceY = 0;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;																	

	char buf[8];
	buf[0] = nowFrequency / 20;
	buf[1] = 0;
	if(aMoveDistanceX > 0 && aMoveDistanceY < 0){
		buf[2] = 'B';
	}
	else if(aMoveDistanceX <= 0 && aMoveDistanceY < 0){
		buf[2] = 'A';
	}
	else if(aMoveDistanceX > 0 && aMoveDistanceY >= 0){
		buf[2] = 'C';
	}
	else if(aMoveDistanceX <= 0 && aMoveDistanceY >= 0){
		buf[2] = 'D';
	}
	Hardware::Serial::changeBufRange(buf, 0, 2);

	if(buf[2] == 'B' || buf[2] == 'A'){
		while(max_freq > nowFrequency){
			buf[0] = nowFrequency / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			nowFrequency = nowFrequency + 100;
			FrequencySwitching::output();
			Sleep(10);	//10ms
		}
		while(mInitFrequency <= nowFrequency){
			buf[0] = nowFrequency / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			nowFrequency = nowFrequency - 100;
			FrequencySwitching::output();
			Sleep(10);	//10ms
		}
		buf[0] = 0;
		for(int i=0; i<aMoveDistanceY/mTimeAjustMentY; i++){
			buf[1] = (500 + i*100) / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			FrequencySwitching::output();
			Sleep(10);
		}
	}

	else{
		buf[0] = 0;
		for(int i=0; i<aMoveDistanceY/mTimeAjustMentY; i++){
			buf[1] = (500 + i*100) / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			FrequencySwitching::output();
			Sleep(10);
		}
		buf[1] = 0;
		while(max_freq > nowFrequency){
			buf[0] = nowFrequency / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			nowFrequency = nowFrequency + 100;
			FrequencySwitching::output();
			Sleep(10);	//10ms
		}
		while(mInitFrequency <= nowFrequency){
			buf[0] = nowFrequency / 20;
			Hardware::Serial::changeBufRange(buf, 0, 2);
			nowFrequency = nowFrequency - 100;
			FrequencySwitching::output();
			Sleep(10);	//10ms
		}

	}

	buf[1] = 0;
	Hardware::Serial::changeBufRange(buf, 0, 2);
	FrequencySwitching::output();
}

}  // namespace Strategy
