#include "FrequencySwitchingX.h"

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX(char aXaxis) :FrequencySwitching(aXaxis)
{
	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;//500 / 10 /2
	}
	mBuf[0] = 0;
	mBuf[1] = 0;
	mBuf[2] = 'B';
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::output()
{
	for (int i = 0; i<freq_up_x_cnt; i++){ //x ¨
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_x_cnt){
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

	for (int i = 0; i<=freq_up_x_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_x_cnt){
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
	mBuf[2] = 'A';
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);

	for (int i = 0; i<freq_up_y_cnt; i++){ //y ª
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[1] = (freq_y_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_y_cnt){
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

	for (int i = 0; i <= freq_up_y_cnt; i++){	
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[1] = (freq_y_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_y_cnt){
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
	mBuf[2] = 'C';
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);

	for (int i = 0; i<freq_up_y_cnt; i++){ //y «
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[1] = (freq_y_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_y_cnt){
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

	for (int i = 0; i <= freq_up_y_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[1] = (freq_y_start) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_y_cnt){
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
	mBuf[2] = 'D';
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);

	for (int i = 0; i<freq_up_x_cnt; i++){ //x ©
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_x_cnt){
			//usleep(10000);	 // 1000=1ms
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

	for (int i = 0; i<=freq_up_x_cnt; i++){
		//closest_frequency = gpioHardwarePWM(18, 500 + freq_up, 500000);
		mBuf[0] = (freq_x_start + freq_up) / 10 / 2;
		mSerial.serialWrite(mBuf, 4);
		if (i<freq_up_x_cnt){
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
	mBuf[2] = 'B';
	mSerial.serialWrite(mBuf, 4);
	//sleep(1);
	Sleep(1000);
	
	for (int i = 0; i < 4; i++){
		mBuf[i] = 0;
	}
	mSerial.serialWrite(mBuf, 4);
}

} /* namespace Strategy */
