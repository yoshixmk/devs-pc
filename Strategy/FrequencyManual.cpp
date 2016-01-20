#include "FrequencyManual.h"

namespace Strategy
{
char FrequencyManual::mBuf[4];

FrequencyManual::FrequencyManual()
{
	mTargetDirection = 'A';
	mFrequencyX = 0;
	int mFrequencyY = 0;
	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;
	}
}

FrequencyManual::~FrequencyManual()
{
}

void FrequencyManual::setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY)
{
	mBuf[0] = aFrequencyX;
	mBuf[1] = aFrequencyY;
	mBuf[2] = aDirection;
}

void FrequencyManual::output()
{
	mSerial.serialWrite(mBuf, 4);
}

}  // namespace Strategy
