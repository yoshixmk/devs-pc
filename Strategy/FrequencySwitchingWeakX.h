#ifndef STRATEGY_FREQUENCYSWITCHING_WEAK_X_H
#define STRATEGY_FREQUENCYSWITCHING_WEAK_X_H

#include "FrequencySwitchingX.h"
#include <windows.h>

namespace Strategy
{

class FrequencySwitchingWeakX: public FrequencySwitchingX
{
public:
	FrequencySwitchingWeakX();

	~FrequencySwitchingWeakX();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHING_WEAK_X_H */
