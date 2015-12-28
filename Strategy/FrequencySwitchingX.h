#ifndef STRATEGY_FREQUENCYSWITCHINGX_H_
#define STRATEGY_FREQUENCYSWITCHINGX_H_

#include "FrequencySwitching.h"
#include <windows.h>

namespace Strategy {

class FrequencySwitchingX: public FrequencySwitching
{
private:
	int mInitFrequency;
	int mFrequencyUpCount;		//周波数を上げる回数
	int mAmountOfChang;			//周波数変化量(Hz)
	double mIntervaTime;		//時間間隔(s)

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
