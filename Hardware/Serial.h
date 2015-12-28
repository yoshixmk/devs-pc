#ifndef HARDWARE_SERIAL_H_
#define HARDWARE_SERIAL_H_

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <math.h>
//送信待ち用にcv::waitKeyを使う
#include <opencv2/highgui/highgui.hpp>  // highguiモジュールのヘッダーをインクルード

namespace Hardware {

class Serial {
private:
	HANDLE mComPort;
	DCB mDcb;
	DWORD mNumberOfPut;
	DWORD mLengthOfSent;
	void serialOpen();
	void serialClose();

public:
	Serial();
	virtual ~Serial();
	void serialWrite(char* buf, int bytes);
};

} /* namespace Hardware */

#endif /* HARDWARE_SERIAL_H_ */
