#include "FrequencyManual.h"

namespace Strategy
{
//char FrequencyManual::mBuf[8];

FrequencyManual::FrequencyManual()
{
	mTargetDirection = 'A';
	mFrequencyX = 100;
	mFrequencyY = 0;
	char buf[8];
	for (int i = 0; i < 8; i++){
		buf[i] = 0;
	}
	buf[2] = 'A';
	buf[5] = 'A';
	Hardware::Serial::changeBufRange(buf, 0, 7);
}

void FrequencyManual::setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY)
{
	char buf[8];
	mFrequencyX = aFrequencyX;
	buf[0] = aFrequencyX / 20;
	mFrequencyY = aFrequencyY;
	buf[1] = aFrequencyY / 20;
	mTargetDirection = buf[2] = aDirection;
	Hardware::Serial::changeBufRange(buf, 0, 2);

	buf[3] = aFrequencyX / 20;
	buf[4] = aFrequencyY / 20;
	buf[5] = mTargetDirection;
	Hardware::Serial::changeBufRange(buf, 3, 5);
}

char FrequencyManual::getTargetDirection()
{
	return mTargetDirection;
}

int FrequencyManual::getFrequencyX()
{
	return mFrequencyX;
}

int FrequencyManual::getFrequencyY()
{
	return mFrequencyY;
}

void FrequencyManual::output()
{
	Hardware::Serial::serialWrite();
}

}  // namespace Strategy
