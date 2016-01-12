#ifndef FREQUENCY_MANUAL_H
#define FREQUENCY_MANUAL_H

#include "../Hardware/Serial.h"

namespace Strategy
{
class FrequencyManual
{
protected:
	Hardware::Serial serial;

public:
	FrequencyManual(void);
	~FrequencyManual(void);
};

}  // namespace Strategy
#endif
