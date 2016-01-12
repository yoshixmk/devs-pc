#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waiting_position;
		waiting_position.x = (FrameCoordinate::getRobotGoalLeft().x + FrameCoordinate::getRobotGoalRight().x) / 2;
		waiting_position.y = (FrameCoordinate::getRobotGoalLeft().y + FrameCoordinate::getRobotGoalRight().y) / 2;

		if (aMalletCoordinate.x < waiting_position.x - 40){
			//ゴールから遠いと速くする
			mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms以上で3500Hz台形
		}
		else if (aMalletCoordinate.x < waiting_position.x - 10){
			//ゴール近辺ならモータの速度を落とす
			mFrequencySwitchingX.setOutputInformation('C', 0.350);
		}
		else if (aMalletCoordinate.x <= waiting_position.x - 3){
			//ゴールに少し近づいてきたら速度を落とす
			mFrequencySwitchingX.setOutputInformation('C', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 3){
			//-3 ~ 3 の範囲は停止
			mFrequencySwitchingX.stop();
		}
		else if (aMalletCoordinate.x < waiting_position.x + 10){
			//ゴールに少し近づいてきたら速度を落とす
			mFrequencySwitchingX.setOutputInformation('D', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 40){
			//ゴール近辺ならモータの速度を落とす
			mFrequencySwitchingX.setOutputInformation('D', 0.350);
		}
		else{
			mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms以上で3500Hz台形
		}

		mFrequencySwitchingX.output();
	}

	void RobotAction::moveToHitBack(CvPoint aPredictedCoordinate, CvPoint aMalletCoordinate)
	{

	}
}  // namespace Strategy
