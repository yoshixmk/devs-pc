#ifndef UI_INTELLIGENT_H
#define UI_INTELLIGENT_H

#include "../Hardware/Serial.h"

namespace UI {
class Intelligent {
private:
	bool mStrongOrWeak;

	Hardware::Serial mSerial;

public:
	Intelligent();

	int getIntelligent();

	bool isStrong();

	bool isWeak();

};

}  // namespace UI
#endif
