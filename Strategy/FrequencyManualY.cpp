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
	mBuf[1] = aFrequencyY / 20;
}

void FrequencyManualY::setOutputInformation(char aDirection, int aFrequencyY)
{
	mBuf[1] = aFrequencyY / 20;
	mBuf[2] = aDirection;
}

void FrequencyManualY::output()
{
	outputY();
}
}  // namespace Strategy
