#include "FrequencySwitchingX.h"

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX(char aXaxis) :FrequencySwitching(aXaxis)
{
	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;//500 / 10 /2
	}
	mBuf[1] = 0;
	mBuf[2] = 'A';
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::output()
{
	for (int i = 0; i<freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mBuf[1] = (freq_y_start) / 10 / 2;
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

	for (int i = 0; i<=freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mBuf[1] = (freq_y_start) / 10 / 2;
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
	mBuf[1] = 0;
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);

	target_direction = 1;
	//gpioWrite(25, target_direction);
	if (target_direction == 0){
		mBuf[2] = 'A';
	}
	else if (target_direction == 1){
		mBuf[2] = 'C';
	}

	for (int i = 0; i<freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mBuf[1] = (freq_y_start) / 10 / 2;
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

	for (int i = 0; i<=freq_up_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mBuf[1] = (freq_y_start) / 10 / 2;
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
	mBuf[1] = 0;
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);
	target_direction = 0;
	//gpioWrite(25, target_direction);
	if (target_direction == 0){
		mBuf[2] = 'A';
	}
	else if (target_direction == 1){
		mBuf[2] = 'C';
	}

	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;
	}
	mSerial.serialWrite(mBuf, 4);
}

} /* namespace Strategy */
