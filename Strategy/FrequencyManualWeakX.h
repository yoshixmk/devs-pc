#ifndef FREQUENCY_MANUAL_WEAK_X_H
#define FREQUENCY_MANUAL_WEAK_X_H

#include "FrequencyManualX.h"

namespace Strategy
{
class FrequencyManualWeakX : public FrequencyManualX
{
public:
	void setOutputInformation(int aFrequencyX);
	void setOutputInformation(char aDirection, int aFrequencyX);
	void setDirection();
	void setFrequencyX();
	void output();
};

}  // namespace Strategy
#endif
