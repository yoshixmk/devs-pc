#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H

#include "OriginRetrun.h"
#include "RobotAction.h"
#include "RobotActionWeak.h"
#include "Locus.h"
#include "MalletCoordinate.h"
#include "PackCoordinate.h"
#include "../Hardware/Timer.h"

namespace Strategy {
class Strategy {

protected:
	Hardware::Timer mTimer;
	HANDLE hMutex; //ミューテックスのハンドル

public:
	//virtual void initialize()=0;

	virtual void execute() = 0;

	//virtual void terminate()=0;

};

}  // namespace Strategy
#endif
