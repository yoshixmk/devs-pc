#ifndef STRATEGY_FREQUENCYSWITCHINGX_H_
#define STRATEGY_FREQUENCYSWITCHINGX_H_

#include "FrequencySwitching.h"
#include <windows.h>

namespace Strategy {

class FrequencySwitchingX: public FrequencySwitching
{
private:
	int target_direction = -1; //目標とする向き　時計回り＝1、　反時計回り＝0

	int closest_frequency;

	int freq_up = 0;
	int freq_up_cnt = 30;		//周波数を上げる回数//21
	int freq_ch = 150;			//周波数切り替え//167
	int freq_ch2 = 100;
	int std_time = 5000/1000;		//中間の間の時間
	char mBuf[4];

public:
	FrequencySwitchingX(char aXaxis = 'X');

	~FrequencySwitchingX();

	void output();

};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHINGX_H_ */
