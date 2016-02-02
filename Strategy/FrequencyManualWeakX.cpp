#include "FrequencyManualWeakX.h"

namespace Strategy
{

void FrequencyManualWeakX::setOutputInformation(int aFrequencyX)
{
	char buf[8];
	mFrequencyX = aFrequencyX;
	buf[3] = aFrequencyX / 20;
	Hardware::Serial::changeBuf(buf, 3);
}

void FrequencyManualWeakX::setOutputInformation(char aDirection, int aFrequencyX)
{
	char buf[8];
	mFrequencyX = aFrequencyX;
	buf[3] = aFrequencyX / 20;
	mTargetDirection = buf[5] = aDirection;
	Hardware::Serial::changeBuf(buf, 3);
	Hardware::Serial::changeBuf(buf, 5);
}

void FrequencyManualWeakX::output()
{
	FrequencyManual::output();
}

}  // namespace Strategy
