#ifndef FREQUENCY_MANUAL_H
#define FREQUENCY_MANUAL_H

#include "../Hardware/Serial.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace Strategy
{
class FrequencyManual
{
protected:
	char mTargetDirection; //'A' 'B' 'C' 'D'
	int mFrequencyX;
	int mFrequencyY;
	static char mBuf[8]; //送信する内容

public:
	FrequencyManual();
	~FrequencyManual();
	void setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY);
	void output();
	void outputX();
	void outputY();
};

}  // namespace Strategy
#endif
