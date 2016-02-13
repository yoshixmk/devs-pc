#include "FrequencyManualY.h"

namespace Strategy
{
FrequencyManualY::FrequencyManualY() :FrequencyManual()
{
}

FrequencyManualY::~FrequencyManualY()
{
}

void FrequencyManualY::setOutputInformation(int aFrequencyY)
{
	char buf[8];
	mFrequencyY = aFrequencyY;
	buf[1] = aFrequencyY / 20;
	Hardware::Serial::changeBuf(buf, 1);
}

void FrequencyManualY::setOutputInformation(char aDirection, int aFrequencyY)
{
	char buf[8];
	mFrequencyY = aFrequencyY;
	buf[1] = aFrequencyY / 20;
	mTargetDirection = buf[2] = aDirection;
	Hardware::Serial::changeBufRange(buf, 1, 2);
}

void FrequencyManualY::output()
{
	FrequencyManual::output();
}
}  // namespace Strategy
