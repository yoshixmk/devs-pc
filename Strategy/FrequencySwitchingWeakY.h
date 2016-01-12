#ifndef STRATEGY_FREQUENCYSWITCHING_WEAK_Y_H
#define STRATEGY_FREQUENCYSWITCHING_WEAK_Y_H

#include "FrequencySwitchingY.h"
#include <windows.h>

namespace Strategy
{

class FrequencySwitchingWeakY: public FrequencySwitchingY
{
public:
	FrequencySwitchingWeakY();

	~FrequencySwitchingWeakY();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHING_WEAK_Y_H */
