#ifndef FREQUENCY_MANUAL_WEAK_Y_H
#define FREQUENCY_MANUAL_WEAK_Y_H

#include "FrequencyManualY.h"

namespace Strategy
{
class FrequencyManualWeakY : public FrequencyManualY
{
public:
	void setOutputInformation(int aFrequencyY);
	void setOutputInformation(char aDirection, int aFrequencyY);
	void setDirection();
	void setFrequencyY();
	void output();
};

}  // namespace Strategy
#endif
