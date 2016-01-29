#include "FrequencyManualX.h"

namespace Strategy
{
FrequencyManualX::FrequencyManualX(void) :FrequencyManual()
{
}


FrequencyManualX::~FrequencyManualX(void)
{
}

void FrequencyManualX::setOutputInformation(int aFrequencyX)
{
	char buf[8];
	mFrequencyX = buf[0] = aFrequencyX / 20;
	Hardware::Serial::changeBuf(buf, 0);
}

void FrequencyManualX::setOutputInformation(char aDirection, int aFrequencyX)
{
	char buf[8];
	mFrequencyX = buf[0] = aFrequencyX / 20;
	mTargetDirection = buf[2] = aDirection;
	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 2);
}

void FrequencyManualX::output()
{
	FrequencyManual::output();
}

}  // namespace Strategy
