#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H

#include "OriginRetrun.h"
#include "RobotAction.h"
#include "Locus.h"
#include "MalletCoordinate.h"
#include "PackCoordinate.h"

namespace Strategy {
class Strategy {
protected:
	OriginRetrun mOriginRetrun;
	RobotAction mRobotAction;
	Locus mLocus;
	MalletCoordinate mMalletCoordinate;
	PackCoordinate mPackCoordinate;

public:
	//virtual void initialize()=0;

	virtual void execute() = 0;

	//virtual void terminate()=0;

};

}  // namespace Strategy
#endif
