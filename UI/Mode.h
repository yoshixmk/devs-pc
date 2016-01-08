#ifndef UI_MODE_H
#define UI_MODE_H

#include "../Strategy/Strategy.h"
#include "Intelligent.h"

namespace UI {
class Mode {
private:
	//Strategy::Strategy strategy;
	Intelligent intelligent;

public:
	virtual void execute()=0;
};

}  // namespace UI
#endif
