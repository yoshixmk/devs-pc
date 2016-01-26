﻿#include "FrequencyManualX.h"

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
	mBuf[1] = aFrequencyX;
}

void FrequencyManualX::setOutputInformation(char aDirection, int aFrequencyX)
{
	mBuf[0] = aFrequencyX;
	mBuf[2] = aDirection;
}

void FrequencyManualX::output()
{
	outputX();
}

}  // namespace Strategy
