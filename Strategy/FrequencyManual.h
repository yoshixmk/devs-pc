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

public:
	FrequencyManual();
	void setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY);
	char getTargetDirection();
	int getFrequencyX();
	int getFrequencyY();
	void output();
};

}  // namespace Strategy
#endif
