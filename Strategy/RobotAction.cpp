#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waiting_position;
		waiting_position.x = (FrameCoordinate::getRobotGoalLeft().x + FrameCoordinate::getRobotGoalRight().x) / 2;
		waiting_position.y = (FrameCoordinate::getRobotGoalLeft().y + FrameCoordinate::getRobotGoalRight().y) / 2;

		if (aMalletCoordinate.x < waiting_position.x - 40){
			//�S�[�����牓���Ƒ�������
			mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms�ȏ��3500Hz��`
		}
		else if (aMalletCoordinate.x < waiting_position.x - 10){
			//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
			mFrequencySwitchingX.setOutputInformation('C', 0.350);
		}
		else if (aMalletCoordinate.x <= waiting_position.x - 3){
			//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
			mFrequencySwitchingX.setOutputInformation('C', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 3){
			//-3 ~ 3 �͈̔͂͒�~
			mFrequencySwitchingX.stop();
		}
		else if (aMalletCoordinate.x < waiting_position.x + 10){
			//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
			mFrequencySwitchingX.setOutputInformation('D', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 40){
			//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
			mFrequencySwitchingX.setOutputInformation('D', 0.350);
		}
		else{
			mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms�ȏ��3500Hz��`
		}

		mFrequencySwitchingX.output();
	}

	void RobotAction::moveToHitBack(CvPoint aPredictedCoordinate, CvPoint aMalletCoordinate)
	{

	}
}  // namespace Strategy
