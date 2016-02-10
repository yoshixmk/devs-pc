#ifndef STRATEGY_FREQUENCY_SWITCHING_WEAK_H
#define STRATEGY_FREQUENCY_SWITCHING_WEAK_H

#include "FrequencySwitching.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

namespace Strategy {
class FrequencySwitchingWeak : public FrequencySwitching
{
public:
	FrequencySwitchingWeak();
	~FrequencySwitchingWeak();
	void setOutputInformation(char aDirection, double aTime);
	void output();
	void stop();
	int getCurrentFrequency();
	void setFrequencyX(int aFrequency);
	void setFrequencyY(int aFrequency);
	void sankakuProcess(int aMoveDistance);
	void sankakuReturnProcess();
	void sankakuUntilHit(int aMoveDistanceX, int aMoveDistanceY);
	void sankakuReturnUntilHit();
	void sankakuRightAngle(int aMoveDistanceX, int aMoveDistanceY);
	void sankakuCenterProcess(int aMoveDistanceX, int aMoveDistanceY);
	//void sankakuReturnRightAngle();
};

}  // namespace Strategy
#endif
