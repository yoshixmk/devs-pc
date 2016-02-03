#include "Serial.h"

namespace Hardware {
HANDLE Serial::mComPort;
DCB Serial::mDcb;
DWORD Serial::mNumberOfPut;
char Serial::mBuf[8];
bool Serial::isOpened = false;
bool Serial::isDebug = false;

void Serial::initialize() {
	if(isOpened == false){
		serialOpen();

		//0だと表示されないバイトは0以外に初期化
		mBuf[2] = 'A';
		mBuf[5] = 'A';
	}
	isOpened = true;
}

void Serial::terminate() {
	if(isOpened == true){
		serialClose();
	}
	isOpened = false;
}

void Serial::serialOpen()
{
	static int first_time;
	if (first_time == 0){
		mComPort = CreateFile("COM6",                //port name
			GENERIC_READ | GENERIC_WRITE, //Read/Write
			0,                            // No Sharing
			NULL,                         // No Security
			OPEN_EXISTING,// Open existing port only
			0,            // Non Overlapped I/O
			NULL);        // Null for Comm Devices

		if (mComPort == INVALID_HANDLE_VALUE)
			std::cout << "Error in opening serial port" << std::endl;
		else
			std::cout << "opening serial port successful" << std::endl;
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

void Serial::serialWrite()
{
	for(int i=0; i<SEND_BYTE; i++){
		if(isDebug == true){
			if(i == 2 || i == 5){
				std::cout << i << ":" << mBuf[i] << " ";
			}
			else{
				printf("%d:%3d ", i,  (int)(unsigned char)mBuf[i]);
			}
		}
	}
	if(isDebug == true){
		std::cout << std::endl;
	}

	WriteFile(mComPort, mBuf, SEND_BYTE, &mNumberOfPut, NULL); // ポートへ送信
}

//すべて上書きした上で、送信
void Serial::serialWrite(char* aBuf)
{
	for(int i=0; i<SEND_BYTE; i++){
		mBuf[i] = aBuf[i];
		if(isDebug == true){
			if(i == 2 || i == 5){
				std::cout << i << ":" << mBuf[i] << " ";
			}
			else{
				printf("%d:%3d ", i,  (int)(unsigned char)mBuf[i]);
			}
		}
	}
	if(isDebug == true){
		std::cout << std::endl;
	}
	WriteFile(mComPort, mBuf, SEND_BYTE, &mNumberOfPut, NULL); // ポートへ送信
}

//changeBufRangeは aFrom=0, aTo=2 のとき、mBuf[0]から[2]まで代入する
void Serial::changeBufRange(char* aBuf, int aFrom, int aTo)
{
	if(aTo < aFrom){
		std::cout << "Serial error. aTo < aFrom" << std::endl;
		exit(-1);
	}
	if(SEND_BYTE < aTo){
		std::cout << "Serial error. aTo buf over." << std::endl;
		exit(-1);
	}
	for(int i=aFrom; i<=aTo; i++){
		mBuf[i] = aBuf[i];
	}
}

void Serial::changeBuf(char* aBuf, int index)
{
	mBuf[index] = aBuf[index];
}

void Serial::setPrintDebug(bool isDebug)
{
	Serial::isDebug = isDebug;
}

} /* namespace Hardware */
