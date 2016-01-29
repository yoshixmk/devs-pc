#include "FrequencyManual.h"

namespace Strategy
{
//char FrequencyManual::mBuf[8];

FrequencyManual::FrequencyManual()
{
	mTargetDirection = 'A';
	mFrequencyX = 100;
	int mFrequencyY = 0;
	char buf[8];
	for (int i = 0; i < 8; i++){
		buf[i] = 0;
	}
	buf[2] = 'A';
	buf[5] = 'A';
	for (int i = 0; i < 8; i++){
		Hardware::Serial::changeBuf(buf, i);
	}
}

FrequencyManual::~FrequencyManual()
{
}

void FrequencyManual::setOutputInformation(char aDirection, int aFrequencyX, int aFrequencyY)
{
	char buf[8];
	mFrequencyX = buf[0] = aFrequencyX / 20;
	mFrequencyY = buf[1] = aFrequencyY / 20;
	mTargetDirection = buf[2] = aDirection;
	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 1);
	Hardware::Serial::changeBuf(buf, 2);
}

void FrequencyManual::output()
{
	Hardware::Serial::serialWrite();
}

/*void FrequencyManual::outputX()
{
	//0バイト目と2バイト目のみを変更して、1回の書き込み
	char buf[8];
	buf[0] = mFrequencyX / 20;
	buf[2] = mTargetDirection;

	Hardware::Serial::changeBuf(buf, 0);
	Hardware::Serial::changeBuf(buf, 2);
	Hardware::Serial::serialWrite();
}
void FrequencyManual::outputY()
{
	//範囲指定して、1回の書き込み
	char buf[8];
	buf[1] = mFrequencyY / 20;
	buf[2] = mTargetDirection;
	Hardware::Serial::changeBuf(buf, 1);
	Hardware::Serial::changeBuf(buf, 2);
	Hardware::Serial::serialWrite();
}*/

}  // namespace Strategy
