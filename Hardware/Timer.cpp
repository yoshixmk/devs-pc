#include "Timer.h"

namespace Hardware {
Timer::Timer(){
	resetStartOperatingTime();
	mStartTime = GetTickCount();
	mNowTime = GetTickCount();
}

void Timer::setTimer(double aNotificationTime) {
	mNotificationTime = aNotificationTime;
	mStartTime = GetTickCount();
	mNowTime = GetTickCount();
}

bool Timer::getAlarm() {
	double passed_time;
	//現在時刻、経過時刻を取得、計算
	mNowTime = GetTickCount();
	passed_time = (double)(mNowTime - mStartTime) / 1000;
	//std::cout<< passed_time <<std::endl;
	//アラーム判定
	if (passed_time >= mNotificationTime) {
		return true;
	} else {
		return false;
	}
}

double Timer::getOperatingTime()
{
	DWORD  now_time;
	double passed_time;
	//現在時刻、経過時刻を取得、計算
	now_time = GetTickCount();
	passed_time = (double)(now_time - mStartOperatingTime) / 1000;
	return passed_time;
}

void Timer::resetStartOperatingTime()
{
	mStartOperatingTime = GetTickCount();
}

}  // namespace Hardware
