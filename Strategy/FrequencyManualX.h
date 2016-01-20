#ifndef FREQUENCY_MANUAL_X_H
#define FREQUENCY_MANUAL_X_H

#include "FrequencyManual.h"

namespace Strategy
{
class FrequencyManualX : public FrequencyManual
{
public:
	FrequencyManualX(void);
	~FrequencyManualX(void);
	void setOutputInformation(int aFrequencyX);
	void setOutputInformation(char aDirection, int aFrequencyX);
	void setDirection();
	void setFrequencyX();
	void output();
};

}  // namespace Strategy
#endif
