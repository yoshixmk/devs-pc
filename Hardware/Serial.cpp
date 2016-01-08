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
	static int first_time;
	if (first_time == 0){
		mComPort = CreateFile("COM4",                //port name
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
		first_time++;
	}

	 // シリアルポートの構成情報が入る構造体
	GetCommState(mComPort, &mDcb); // 現在の設定値を読み込み

	mDcb.BaudRate = 115200; // 速度
	mDcb.ByteSize = 8; // 通信データ長
	mDcb.Parity = NOPARITY; // パリティ
	mDcb.StopBits = ONESTOPBIT; // ストップビット長
	mDcb.fOutxCtsFlow = FALSE; // ハードウェアフロー制御 送信時CTSフロー
	mDcb.fOutX = FALSE; // ソフトウェアフロー制御 送信時XON/OFF制御の有無
	mDcb.fRtsControl = RTS_CONTROL_ENABLE; // RTSフロー
	SetCommState(mComPort, &mDcb); // 変更した設定値を書き込み
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
