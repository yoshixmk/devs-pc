#include "Serial.h"

namespace Hardware {

Serial::Serial() {
	serialOpen();
}

Serial::~Serial() {
	serialClose();
}

void Serial::serialOpen()
{
	mComPort = CreateFile(_T("COM5"),                //port name
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,                            // No Sharing
		NULL,                         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);        // Null for Comm Devices

	if (mComPort == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port");
	else
		printf("opening serial port successful");

	DCB dcb; // シリアルポートの構成情報が入る構造体
	GetCommState(mComPort, &dcb); // 現在の設定値を読み込み

	dcb.BaudRate = 115200; // 速度
	dcb.ByteSize = 8; // 通信データ長
	dcb.Parity = NOPARITY; // パリティ
	dcb.StopBits = ONESTOPBIT; // ストップビット長
	dcb.fOutxCtsFlow = FALSE; // ハードウェアフロー制御 送信時CTSフロー
	dcb.fOutX = FALSE; // ソフトウェアフロー制御 送信時XON/OFF制御の有無
	SetCommState(mComPort, &dcb); // 変更した設定値を書き込み
}

void Serial::serialClose()
{
	CloseHandle(mComPort);
}

void Serial::serialWrite(char* aBuf, int aBytes)
{
	mLengthOfSent = aBytes; // 送信する文字数
	 WriteFile(mComPort, aBuf, mLengthOfSent, &mNumberOfPut, NULL); // ポートへ送信
	cv::waitKey(10);
}

} /* namespace Hardware */
