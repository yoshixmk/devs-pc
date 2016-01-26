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
	void serialOpen();
	void serialClose();
	static char mBuf[8];
	static bool isOpened;
	static const int SEND_BYTE=8; // 送信する文字数

public:
	Serial();
	virtual ~Serial();
	void serialWrite(char* aBuf);
	void setWriteRange(char* aBuf, int aFrom, int aTo);
};

} /* namespace Hardware */

#endif /* HARDWARE_SERIAL_H_ */
