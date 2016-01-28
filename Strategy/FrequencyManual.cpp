#include "FrequencyManual.h"

namespace Strategy
{
char FrequencyManual::mBuf[8];

FrequencyManual::FrequencyManual()
{
	mTargetDirection = 'A';
	mFrequencyX = 100;
	int mFrequencyY = 0;
	for (int i = 0; i < 8; i++){
		mBuf[i] = 0;
	}
}

FrequencyManual::~FrequencyManual()
{
}

void FrequencyManual::setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY)
{
	mBuf[0] = aFrequencyX / 20;
	mBuf[1] = aFrequencyY / 20;
	mBuf[2] = aDirection;
}

void FrequencyManual::output()
{
	Hardware::Serial::serialWrite();
}

void FrequencyManual::outputX()
{
	//0バイト目と2バイト目のみを変更して、1回の書き込み
	Hardware::Serial::changeBuf(mBuf, 0);
	Hardware::Serial::changeBuf(mBuf, 2);
	Hardware::Serial::serialWrite();
}
void FrequencyManual::outputY()
{
	//範囲指定して、1回の書き込み
	Hardware::Serial::serialWriteRange(mBuf, 1, 2);
}

}  // namespace Strategy
