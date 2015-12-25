#include "FrequencySwitchingX.h"

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX(char aXaxis) :FrequencySwitching(aXaxis)
{
	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;//500 / 10 /2
	}
	mBuf[2] = 'A';
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

void FrequencySwitchingX::output()
{
	//ŽŸ‰ñ‚±‚±‚©‚ç
	//if (mTimer.getOperatingTime() < 0.01){//10ms

	//}
	for (int i = 0; i<freq_up_cnt; i++){
		mBuf[0] = (500 + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_cnt){
			//usleep(10000);	//10ms
			Sleep(10);
			freq_up = freq_up + freq_ch;
		}
		
		/*else{
		usleep(5000);	//10ms
		freq_up=freq_up+freq_ch2;
		closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
		}*/
	}
	//usleep(std_time);
	Sleep(std_time);

	for (int i = 0; i<freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (500 + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_cnt){
			//usleep(10000);	//10ms
			Sleep(10);
			freq_up = freq_up - freq_ch;
		}
		
		/*else{
		usleep(5000);	//10ms
		freq_up=freq_up-freq_ch2;
		closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
		}*/
	}

	//closest_frequency = gpioHardwarePWM(18, 0, 500000);
	mBuf[0] = 0;
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);

	target_direction = 1;
	//gpioWrite(25, target_direction);
	if (target_direction == 0){
		mBuf[2] = 'A';
	}
	else if (target_direction == 1){
		mBuf[2] = 'B';
	}

	for (int i = 0; i<freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (500 + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_cnt){
			//usleep(10000);	 // 1000=1ms
			Sleep(1);
			freq_up = freq_up + freq_ch;
		}
		
		/*else{
		usleep(5000);	//10ms
		freq_up=freq_up+freq_ch2;
		closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
		}*/

	}
	//usleep(std_time);
	Sleep(std_time);

	for (int i = 0; i<freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (500 + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_cnt){
			//usleep(10000);	//10ms
			Sleep(10);
			freq_up = freq_up - freq_ch;
		}
		
		/*else{
		usleep(5000);	//10ms
		freq_up=freq_up-up-freq_ch;
		closest_frequency = gpioHardwarePWM(18, 500+freq_up2,500000);
		}*/
	}
	//closest_frequency = gpioHardwarePWM(18, 0, 500000);
	mBuf[0] = 0;
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);
	target_direction = 0;
	//gpioWrite(25, target_direction);
	if (target_direction == 0){
		mBuf[2] = 'A';
	}
	else if (target_direction == 1){
		mBuf[2] = 'B';
	}

	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;
	}
	mSerial.serialWrite(mBuf, 4);
}

void stop(){

}

int getCurrentFrequency(){
	return 0;
}

} /* namespace Strategy */
