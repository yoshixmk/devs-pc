#ifndef HARDWARE_SERIAL_H_
#define HARDWARE_SERIAL_H_

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <math.h>
//送信待ち用にcv::waitKeyを使う
#include "../CLEye/opencv.hpp"  // highguiモジュールのヘッダーをインクルード

namespace Hardware {

class Serial {
private:
	HANDLE mComPort;
	DCB mDcb;
	DWORD mNumberOfPut;
	DWORD mLengthOfSent;
	void serialOpen();
	void serialClose();
	char mBuf[8];

public:
	Serial();
	virtual ~Serial();
	void serialWrite(char* aBuf, int aBytes);
	void setWriteRange(char* aBuf, int aFrom, int aTo);
};

} /* namespace Hardware */

#endif /* HARDWARE_SERIAL_H_ */
