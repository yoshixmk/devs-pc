#ifndef TEST_STRATEGYTEST_H
#define TEST_STRATEGYTEST_H

#include "../Strategy/PackCoordinate.h"
#include "../Strategy/MalletCoordinate.h"
#include "../Strategy/FrameCoordinate.h"
#include "../Strategy/Locus.h"
#include "../Strategy/FrequencySwitching.h"
#include "../Strategy/FrequencySwitchingX.h"
#include "../Strategy/FrequencySwitchingY.h"
#include "../Strategy/RobotAction.h"
#include "../Strategy/FrequencyManual.h"
#include "../Strategy/FrequencyManualX.h"
#include "../Strategy/FrequencyManualY.h"
#include "../Strategy/RobotAction.h"
#include "../Strategy/Strategy.h"
#include "../Strategy/OffenseDefenseStrategy.h"
#include "../Strategy/SpeedOfPack.h"

#include "../Hardware/Camera.h"
#include "../Hardware/Timer.h"

#include <iostream>
#include <windows.h>

namespace Test {
	class StrategyTest {
	private:

	public:
		StrategyTest();
		void packCoordinateTest();
		void malletCoordinateTest();
		void frameCoordinateTest();
		void locusTest();
		void frequencySwitchingTest();
		void frequencySwitching_X_Test();
		void frequencySwitching_Y_Test();
		void frequencyTest();
		void frequency_X_Test();
		void frequency_Y_Test();
		void frequencyManualTest();
		void frequencyManualXTest();
		void frequencyManualYTest();
		void offenseDeffenseStrategyTest();
		void speedOfPackTest();
		void robotActionCenterTest();
		void robotActionHitBackTest();
		void robotActionSankakuTest();
		void robotActionSankakuCenterBackTest();
		void robotActionSideGuardTest();
		void robotActionAlarmHitBackTest();
		void robotActionMoveRightAngleTest();
	};

}  // namespace Test
#endif