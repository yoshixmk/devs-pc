#ifndef FREQUENCY_MANUAL_Y_H
#define FREQUENCY_MANUAL_Y_H

#include "FrequencyManual.h"

namespace Strategy
{
class FrequencyManualY : public FrequencyManual
{
public:
	FrequencyManualY();
	~FrequencyManualY();
	void setOutputInformation(char aDirection, int aFrequencyY);
	void setDirection();
	void setFrequencyY();
	void output();
};

}  // namespace Strategy
#endif
