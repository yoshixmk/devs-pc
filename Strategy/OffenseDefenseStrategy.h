#ifndef STRATEGY_OFFENSE_DEFENSE_STRATEGY_H
#define STRATEGY_OFFENSE_DEFENSE_STRATEGY_H

#include "Strategy.h"
#include "PackCoordinate.h"
#include "MalletCoordinate.h"
#include "Locus.h"
#include "RobotAction.h"
#include "RobotActionWeak.h"
#include "FrameCoordinate.h"

#include <stdio.h>
#include <windows.h>
#include <process.h>

namespace Strategy {
class OffenseDefenseStrategy: public Strategy {
private:

public:
	//void initialize();
	void execute();
	//void terminate();
};

}  // namespace Strategy
#endif
