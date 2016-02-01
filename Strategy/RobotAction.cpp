#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = 421;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToRightCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 25;
		waitingPosition.y = 421;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}
	void RobotAction::moveToLeftCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 25;
		waitingPosition.y = 421 + 1; //�摜�������΂߂̂���
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}
	void RobotAction::moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition)
	{
		int xMargin = 3;
		int yMargin = 5;
		//X
		if(aWaitingPosition.x - xMargin < aMalletCoordinate.x && aMalletCoordinate.x < aWaitingPosition.x + xMargin){//��ʒu�t��
			//-3 �` 3 �͈̔͂͒�~
			//mFrequencySwitchingX.stop();
			mFrequencyManualX.setOutputInformation(0);
			
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //��ʒu�t�߂łȂ��Ȃ�
				mFrequencyManualY.setOutputInformation('D', 500);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('A', 500);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		else if(aMalletCoordinate.x <= aWaitingPosition.x - xMargin){ //B�܂���C�̕���
			if (aMalletCoordinate.x < aWaitingPosition.x - 40){
				//�S�[�����牓���Ƒ�������
				//mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms�ȏ��3500Hz��`
				mFrequencyManualX.setOutputInformation('C', 400);
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x - 10){
				//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
				//mFrequencySwitchingX.setOutputInformation('C', 0.350);
				mFrequencyManualX.setOutputInformation('C', 300);
			}
			else if (aMalletCoordinate.x <= aWaitingPosition.x){
				//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
				mFrequencyManualX.setOutputInformation('C', 0.200);
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //��ʒu�t�߂łȂ��Ȃ�
				mFrequencyManualY.setOutputInformation('C', 500);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('B', 500);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		else if(aWaitingPosition.x + xMargin <= aMalletCoordinate.x){ //A�܂���D�̕���
			if (aMalletCoordinate.x < aWaitingPosition.x + 10){
				//�S�[���ɏ����߂Â��Ă����瑬�x�𗎂Ƃ�
				//mFrequencySwitchingX.setOutputInformation('D', 0.200);
				mFrequencyManualX.setOutputInformation('D', 100);
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x + 40){
				//�S�[���ߕӂȂ烂�[�^�̑��x�𗎂Ƃ�
				//mFrequencySwitchingX.setOutputInformation('D', 0.350);
				mFrequencyManualX.setOutputInformation('D', 300);
			}
			else{
				//mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms�ȏ��3500Hz��`
				mFrequencyManualX.setOutputInformation('D', 400);
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //��ʒu�t�߂łȂ��Ȃ�
				mFrequencyManualY.setOutputInformation('D', 500);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('A', 500);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		mFrequencyManual.output();
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

	void RobotAction::sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		//���~�b�g�X�C�b�`�ɓ������Ă��܂�Ȃ��悤�ɕ␳
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		if(forecastPackCoordinate.x < 33){//45
			forecastPackCoordinate.x = 33;
		}
		if(forecastPackCoordinate.x > 290){//280
			forecastPackCoordinate.x = 290;
		}
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		mFrequencySwitching.sankakuProcess(moveDistance);
	}

	void RobotAction::sankakuCenterBack()
	{
		mFrequencySwitching.sankakuReturnProcess();
	}

	void RobotAction::sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		//���~�b�g�X�C�b�`�ɓ������Ă��܂�Ȃ��悤�ɕ␳
		CvPoint packCoordinate = aPackCoordinate;
		if(packCoordinate.x < 33){//45
			packCoordinate.x = 33;
		}
		if(packCoordinate.x > 290){//280
			packCoordinate.x = 290;
		}
		int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
		int moveDistanceY = aMalletCoordinate.y - packCoordinate.y;
		if(moveDistanceY < 0){
			moveDistanceY = 0;
		}
		mFrequencySwitching.sankakuUntilHit(moveDistanceX, moveDistanceY);
	}

	void RobotAction::sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		if(FrameCoordinate::getCenterLine().x+3 < aPackCoordinate.x){
			moveToRightCenter(aMalletCoordinate);
		}
		else if(aPackCoordinate.x < FrameCoordinate::getCenterLine().x-3){
			moveToLeftCenter(aMalletCoordinate);
		}
		else{
			moveToCenter(aMalletCoordinate);
		}
	}

	void RobotAction::alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		if(FrameCoordinate::getCenterLine().y + 30 < aPackCoordinate.y && aPackCoordinate.y < 400){
			if(mTimer.getOperatingTime() > 2){ //��莞�Ԉȏ�A���t�B�[���h�Ƀp�b�N������Ƃ�
				sankakuUntilHit(aMalletCoordinate, aPackCoordinate);
				sankakuCenterBack();
				mTimer.resetStartOperatingTime();
			}
		}
		else if(400 <= aPackCoordinate.y){
			if(mTimer.getOperatingTime() > 2){ //��莞�Ԉȏ�A���t�B�[���h�Ƀp�b�N������Ƃ�
				moveRightAngle(aMalletCoordinate, aPackCoordinate);
				//���~�b�g�X�C�b�`�ɓ������Ă��܂�Ȃ��悤�ɕ␳
				/*CvPoint packCoordinate = aPackCoordinate;
				if(packCoordinate.x < 33){//45
					packCoordinate.x = 33;
				}
				if(packCoordinate.x > 290){//280
					packCoordinate.x = 290;
				}
				int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
				int moveDistanceY = aMalletCoordinate.y - packCoordinate.y;
				if(moveDistanceY < 0){
					moveDistanceY = 0;
				}
				mFrequencySwitching.sankakuRightAngle(moveDistanceX, moveDistanceY);
				mFrequencySwitching.sankakuReturnProcess();
				mTimer.resetStartOperatingTime();*/
			}
		}
		else{
			mTimer.resetStartOperatingTime();
		}
	}

	void RobotAction::moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		if(mFrequencyManualX.getFrequencyX() == 0 && mFrequencyManualY.getFrequencyY() == 0){
			//���~�b�g�X�C�b�`�ɓ������Ă��܂�Ȃ��悤�ɕ␳
			CvPoint packCoordinate = aPackCoordinate;
			if(packCoordinate.x < 33){//45
				packCoordinate.x = 33;
			}
			if(packCoordinate.x > 290){//280
				packCoordinate.x = 290;
			}
			int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
			int moveDistanceY = packCoordinate.y - aMalletCoordinate.y;
			if(moveDistanceY < 0){
				moveDistanceY = 0;
			}
			mFrequencySwitching.sankakuRightAngle(moveDistanceX, moveDistanceY);
			mFrequencySwitching.sankakuReturnProcess();
		}
		else{
			moveToCenter(aMalletCoordinate);
		}
	}
}  // namespace Strategy
