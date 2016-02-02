#include "FrequencyManualWeakY.h"

namespace Strategy
{

void FrequencyManualWeakY::setOutputInformation(int aFrequencyY)
{
	char buf[8];
	mFrequencyY = aFrequencyY;
	buf[4] = aFrequencyY / 20;
	Hardware::Serial::changeBuf(buf, 4);
}

void FrequencyManualWeakY::setOutputInformation(char aDirection, int aFrequencyY)
{
	char buf[8];
	mFrequencyY = aFrequencyY;
	buf[4] = aFrequencyY / 20;
	mTargetDirection = buf[5] = aDirection;
	Hardware::Serial::changeBufRange(buf, 4, 5);
}

void FrequencyManualWeakY::output()
{
	FrequencyManual::output();
}
}  // namespace Strategy
