#ifndef STRATEGY_FREQUENCYSWITCHINGX_H_
#define STRATEGY_FREQUENCYSWITCHINGX_H_

#include "FrequencySwitching.h"
#include <windows.h>

namespace Strategy {

class FrequencySwitchingX: public FrequencySwitching
{
private:
	//mIsRightX 目標とする向き　時計回り＝1、　反時計回り＝0

	int closest_frequency;

	int freq_up = 0;
	int mFrequencyUpCount = 32;		//周波数を上げる回数
	int mAmountOfChang = 100;			//周波数変化量(Hz)
	int std_time = 5000/1000;		//中間の間の時間

public:
	FrequencySwitchingX();

	~FrequencySwitchingX();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();

};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHINGX_H_ */
