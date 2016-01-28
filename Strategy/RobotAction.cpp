#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waiting_position;
		waiting_position.x = (FrameCoordinate::getRobotGoalLeft().x + FrameCoordinate::getRobotGoalRight().x) / 2;
		waiting_position.y = 405;

		if (aMalletCoordinate.x < waiting_position.x - 40){
			//�S�[�����牓���Ƒ�������
			//mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms�ȏ��3500Hz��`
			mFrequencyManualX.setOutputInformation('C', 300);
		}
		else if (aMalletCoordinate.x < waiting_position.x - 10){
			//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
			//mFrequencySwitchingX.setOutputInformation('C', 0.350);
			mFrequencyManualX.setOutputInformation('C', 200);
		}
		else if (aMalletCoordinate.x <= waiting_position.x - 3){
			//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
			mFrequencyManualX.setOutputInformation('C', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 3){
			//-3 ~ 3 �͈̔͂͒�~
			//mFrequencySwitchingX.stop();
			mFrequencyManualX.setOutputInformation(0);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 10){
			//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
			//mFrequencySwitchingX.setOutputInformation('D', 0.200);
			mFrequencyManualX.setOutputInformation('D', 100);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 40){
			//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
			//mFrequencySwitchingX.setOutputInformation('D', 0.350);
			mFrequencyManualX.setOutputInformation('D', 200);
		}
		else{
			//mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms�ȏ��3500Hz��`
			mFrequencyManualX.setOutputInformation('D', 300);
		}

		if(aMalletCoordinate.y < waiting_position.y){ //��ʒu���㑤�Ȃ�
			mFrequencyManualY.setOutputInformation(500);
		}
		else
			mFrequencyManualY.setOutputInformation(0);{
		}

		mFrequencyManualX.output();
		mFrequencyManualY.output();
	}

	bool RobotAction::moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		//���~�b�g�X�C�b�`�ɓ������Ă��܂�Ȃ��悤�ɕ␳
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		if(forecastPackCoordinate.x < 60){
			forecastPackCoordinate.x = 60;
		}
		if(forecastPackCoordinate.x > 270){
			forecastPackCoordinate.x = 270;
		}
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		printf("moveDistance:%d\n", moveDistance);
		//moveDistance�̓p�b�N��
		//�E�ɔ��ł���\�z�̏ꍇ�{�A���ɔ��ł���\�z�̏ꍇ�|
		//mFrequencySwitching.sankakuProcess(moveDistance);
		//FrequencyManual::FrequencyManual();
		if(abs(moveDistance) < 3)
		{
			mFrequencyManualX.setOutputInformation('A', 0);
			mFrequencyManualX.output();
			//mFrequencyManualY.output();
			return true;
		}
		else if(moveDistance >= 3)
		{
			mFrequencyManualX.setOutputInformation('C', 300);
			mFrequencyManualX.output();
			//mFrequencyManualY.output();
		}
		else if(moveDistance <= -3)
		{
			mFrequencyManualX.setOutputInformation('D', 300);
			mFrequencyManualX.output();
			//mFrequencyManualY.output();
		}

		return false;
	}
}  // namespace Strategy
