#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include <iostream>
#include <vector>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

namespace Hardware {
class Timer {
private:
	DWORD mStartTime;
	DWORD mNowTime;
	double mNotificationTime;
	DWORD mStartOperatingTime;

public:
	Timer();
	void setTimer(double aNotificationTime);
	bool getAlarm();
	double getOperatingTime();
	void resetStartOperatingTime();

};

}  // namespace Hardware
#endif
