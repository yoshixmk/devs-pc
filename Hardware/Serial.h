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
	static HANDLE mComPort;
	static DCB mDcb;
	static DWORD mNumberOfPut;
	static char mBuf[8];
	static bool isOpened;
	static bool isDebug;
	static const int SEND_BYTE=8; // 送信する文字数
	static void serialOpen();
	static void serialClose();

public:
	static void initialize();
	static void terminate();
	static void serialWrite();
	static void serialWrite(char* aBuf);
	static void changeBufRange(char* aBuf, int aFrom, int aTo);
	static void changeBuf(char* aBuf, int index);
	static void setPrintDebug(bool isDebug);
};

} /* namespace Hardware */

#endif /* HARDWARE_SERIAL_H_ */
