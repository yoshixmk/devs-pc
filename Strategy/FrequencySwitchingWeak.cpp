#include "FrequencySwitchingWeak.h"

namespace Strategy
{

FrequencySwitchingWeak::FrequencySwitchingWeak()
{
	mCurrentFrequency = 0;
	mTargetTime = 0;
	mTargetDirection = 'A';
	mTargetTime = 0;

	mTimeAjustMentY = 2;
	mInitFrequency = 400;
}

FrequencySwitchingWeak::~FrequencySwitchingWeak()
{
}

void FrequencySwitchingWeak::setOutputInformation(char aTargetDirection, double aTargetTime)
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
	buf[5] = mTargetDirection;
	Hardware::Serial::changeBuf(buf, 5);
}

void FrequencySwitchingWeak::output()
{
	Hardware::Serial::serialWrite();
}

void FrequencySwitchingWeak::stop()
{
	char buf[8];
	buf[3] = 0;
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 4);
	Hardware::Serial::serialWrite();
}

void FrequencySwitchingWeak::setFrequencyX(int aFrequency){
	char buf[8];
	buf[3] = aFrequency;
	Hardware::Serial::changeBuf(buf, 3);
}

void FrequencySwitchingWeak::setFrequencyY(int aFrequency){
	char buf[8];
	buf[4] = aFrequency;
	Hardware::Serial::changeBuf(buf, 4);
}

void FrequencySwitchingWeak::sankakuProcess(int aMoveDistance)
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
	buf[3] = nowFrequency / 20;
	buf[4] = 500 / 20;
	if(aMoveDistance > 0){
		buf[5] = 'B';
	}
	else{
		buf[5] = 'A';
	}
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();

	while(max_freq > nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
		yCount++;
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
		yCount++;
	}
	buf[3] = 0;
	for(;yCount < yTargetCount; yCount++){
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
	}
	buf[3] = 0;
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();
}

void FrequencySwitchingWeak::sankakuDefense(int aMoveDistanse)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50; //100
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistanse);
	int yTargetCount = 30;
	int yCount = 0;
	mMoveDistanceX = aMoveDistanse;
	mMoveDistanceY = 0;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;

	char buf[8];
	buf[3] = nowFrequency / 20;
	buf[4] = 0;
	if(aMoveDistanse > 0){
		buf[5] = 'B';
	}
	else{
		buf[5] = 'A';
	}
	
	buf[3]=0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	Sleep(10);
	while(max_freq > nowFrequency){
		buf[0] = nowFrequency / 20;
		//マルチタスクで更新タイミング考慮のため、全て更新
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
		yCount++;
	}
	buf[3] = 0;
	Hardware::Serial::changeBuf(buf, 3);

	buf[3] = 0;
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitching::output();
	Sleep(10);
}

void FrequencySwitchingWeak::sankakuReturnProcess()
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
	buf[3] = nowFrequency / 20;
	buf[4] = 500 / 20;
	if(mMoveDistanceX > 0){
		buf[5] = 'D';
	}
	else{
		buf[5] = 'C';
	}
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();

	while(max_freq > nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	buf[3] = 0;
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();
}

void FrequencySwitchingWeak::sankakuUntilHit(int aMoveDistanceX, int aMoveDistanceY)
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
	buf[3] = nowFrequency / 20;
	buf[4] = 500 / 20;
	if(aMoveDistanceX > 0){
		buf[5] = 'B';
	}
	else{
		buf[5] = 'A';
	}
	Hardware::Serial::changeBufRange(buf, 3, 5);

	while(max_freq > nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitching::output();
		Sleep(10);	//10ms
	}
	buf[3] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();

	int loopTime = aMoveDistanceY/mTimeAjustMentY;
	if(loopTime > 15){
		loopTime = 15;
	}
	for(int i=0; i<loopTime; i++){ //Yの距離から時間の変換
		buf[1] = (500 + i*150) / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitching::output();
		Sleep(10);
	}
	for(int i=2; 0<=i; i--){
		buf[1] = 500 + i*150;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitching::output();
		Sleep(10);
	}
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();
}

void FrequencySwitchingWeak::sankakuRightAngle(int aMoveDistanceX, int aMoveDistanceY)
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
	buf[3] = nowFrequency / 20;
	buf[4] = 0;
	if(aMoveDistanceX > 0){
		buf[5] = 'B';
	}
	else{
		buf[5] = 'A';
	}
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();

	while(max_freq > nowFrequency){
		buf[3] = nowFrequency / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
	}
	buf[3] = 0;
	Hardware::Serial::changeBuf(buf, 3);
	int loopTime = aMoveDistanceY/mTimeAjustMentY;
	if(loopTime > 21){
		loopTime = 21;
	}
	for(int i=0; i<loopTime; i++){
		buf[4] = (500 + i*100) / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitchingWeak::output();
		Sleep(10);
	}

	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();
}

void FrequencySwitchingWeak::sankakuCenterProcess(int aMoveDistanceX, int aMoveDistanceY)
{
	int closest_frequency;
	float ossum = 0;
	float sum = 0.176;
	float next_freq = 0;
	int max_freq = 50; //100
	int freq =0;
	int nowFrequency = mInitFrequency;
	int moveDistanceAbs = abs(aMoveDistanceX);
	int yTargetCount = 50;
	int yCount = 0;
	mMoveDistanceX = aMoveDistanceX;
	mMoveDistanceY = aMoveDistanceY;

	while(moveDistanceAbs >= next_freq * 2){
		next_freq = next_freq + sum +0.20*freq;
		freq++;
		max_freq = max_freq + 100;
	}
	max_freq = max_freq - 100;

	char buf[8];
	buf[3] = nowFrequency / 20;
	buf[4] = 500 / 20;
	if(aMoveDistanceX > 0){
		buf[5] = 'C';
	}
	else{
		buf[5] = 'D';
	}
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();

	while(max_freq > nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency + 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
		yCount++;
	}
	while(mInitFrequency <= nowFrequency){
		buf[3] = nowFrequency / 20;
		buf[4] = 500 / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		nowFrequency = nowFrequency - 100;
		FrequencySwitchingWeak::output();
		Sleep(10);	//10ms
		yCount++;
	}
	buf[3] = 0;
	int loopTime = aMoveDistanceY/mTimeAjustMentY;
	if(loopTime > 23){
		loopTime = 23;
	}
	for(int i=0; i<loopTime; i++){
		buf[4] = (500 + i*100) / 20;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitchingWeak::output();
		Sleep(10);
	}
	for(int i=2; 0<=i; i--){
		buf[4] = 500 + i*150;
		Hardware::Serial::changeBufRange(buf, 3, 5);
		FrequencySwitching::output();
		Sleep(10);
	}
	buf[3] = 0;
	buf[4] = 0;
	Hardware::Serial::changeBufRange(buf, 3, 5);
	FrequencySwitchingWeak::output();
}

}  // namespace Strategy
