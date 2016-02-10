#include "RobotAction.h"

namespace Strategy {
	RobotAction::RobotAction()
	{
		//default value
		mCenterYLine = 426;
	}

	void RobotAction::setCenterYLine(int aCenterYLine)
	{
		mCenterYLine = aCenterYLine;
	}

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToCenterDefense(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = 432;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::guardCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = 426;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToRightCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 35;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToRightCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 35;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToLeftCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 35;
		waitingPosition.y = mCenterYLine + 1; //画像が少し斜めのため
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToLeftCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 35;
		waitingPosition.y = mCenterYLine + 1; //画像が少し斜めのため
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition)
	{
		int xMargin = 3;
		int yMargin = 5;
		int maxSpeedUp = 2000;

		if(mMoveingTimer.getOperatingTime() > 1.0){
			mMoveingTimer.resetStartOperatingTime();
		}
		//X
		if(aWaitingPosition.x - xMargin < aMalletCoordinate.x && aMalletCoordinate.x < aWaitingPosition.x + xMargin){//定位置付近
			mCenterFrequencyManualX.setOutputInformation(0);
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
				mFrequencyManualY.setOutputInformation('D', 500);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('A', 500);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
			mMoveingTimer.resetStartOperatingTime();
		}
		else if(aMalletCoordinate.x <= aWaitingPosition.x - xMargin){ //BまたはCの方向
			if (aMalletCoordinate.x < aWaitingPosition.x - 40){
				//ゴールから遠いと速くする。10ms以上時間が経過していればに+100加速
				int nowMaxSpeed = 300 + (int)(mMoveingTimer.getOperatingTime() * 80) * 100; //100 -> 80
				int frequencyX = mCenterFrequencyManualX.getFrequencyX();
				if(frequencyX + 100 < nowMaxSpeed){
					frequencyX += 100;
				}
				else{
					frequencyX = 300;
					mMoveingTimer.resetStartOperatingTime();
				}
				if(frequencyX > maxSpeedUp){
					frequencyX = maxSpeedUp;
				}
				if(mCenterFrequencyManualX.getTargetDirection() == 'B' || mCenterFrequencyManualX.getTargetDirection() == 'C'){
					mCenterFrequencyManualX.setOutputInformation('C', frequencyX);
				}
				else{
					mCenterFrequencyManualX.setOutputInformation('C', 300);
					mMoveingTimer.resetStartOperatingTime();
				}
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x - 10){
				//ゴール近辺ならモータの速度を落とす
				mCenterFrequencyManualX.setOutputInformation('C', 300);
				mMoveingTimer.resetStartOperatingTime();
			}
			else if (aMalletCoordinate.x <= aWaitingPosition.x){
				//ゴールに少し近づいてきたら速度を落とす
				mCenterFrequencyManualX.setOutputInformation('C', 0.200);
				mMoveingTimer.resetStartOperatingTime();
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
				mFrequencyManualY.setOutputInformation('C', 500);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('B', 500);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		else if(aWaitingPosition.x + xMargin <= aMalletCoordinate.x){ //AまたはDの方向
			if (aMalletCoordinate.x < aWaitingPosition.x + 10){
				//ゴールに少し近づいてきたら速度を落とす
				mCenterFrequencyManualX.setOutputInformation('D', 100);
				mMoveingTimer.resetStartOperatingTime();
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x + 40){
				//ゴール近辺ならモータの速度を落とす
				mCenterFrequencyManualX.setOutputInformation('D', 300);
				mMoveingTimer.resetStartOperatingTime();
			}
			else{
				//ゴールから遠いと速くする。10ms以上時間が経過していればに+100加速
				int nowMaxSpeed = 400 + (int)(mMoveingTimer.getOperatingTime() * 100) * 100;
				int frequencyX = mCenterFrequencyManualX.getFrequencyX();
				if(frequencyX + 100 < nowMaxSpeed){
					frequencyX += 100;
				}
				else{
					frequencyX = 400;
					mMoveingTimer.resetStartOperatingTime();
				}
				if(frequencyX > maxSpeedUp){
					frequencyX = maxSpeedUp;
				}
				if(mCenterFrequencyManualX.getTargetDirection() == 'A' || mCenterFrequencyManualX.getTargetDirection() == 'D'){
					mCenterFrequencyManualX.setOutputInformation('D', frequencyX);
				}
				else{
					mCenterFrequencyManualX.setOutputInformation('D', 400);
					mMoveingTimer.resetStartOperatingTime();
				}
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
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
		//リミットスイッチに当たってしまわないように補正
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		if(forecastPackCoordinate.x < 33){
			forecastPackCoordinate.x = 33;
		}
		if(forecastPackCoordinate.x > 290){
			forecastPackCoordinate.x = 290;
		}
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		//moveDistanceはパックが
		//右に飛んでくる予想の場合＋、左に飛んでくる予想の場合－
		if(abs(moveDistance) < 3)
		{
			mFrequencyManualX.setOutputInformation('A', 0);
			mFrequencyManualX.output();
			return true;
		}
		else if(moveDistance >= 3)
		{
			mFrequencyManualX.setOutputInformation('C', 300);
			mFrequencyManualX.output();
		}
		else if(moveDistance <= -3)
		{
			mFrequencyManualX.setOutputInformation('D', 300);
			mFrequencyManualX.output();
		}

		return false;
	}

	void RobotAction::sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		mFrequencySwitching.sankakuProcess(moveDistance);
	}

	void RobotAction::sankakuDefense(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		//リミットスイッチに当たってしまわないように補正
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		mFrequencySwitching.sankakuDefense(moveDistance);
	}

	void RobotAction::sankakuCenterBack()
	{
		mFrequencySwitching.sankakuReturnProcess();
	}

	void RobotAction::sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		CvPoint packCoordinate = aPackCoordinate;
		int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
		int moveDistanceY = abs(packCoordinate.y - aMalletCoordinate.y);
		mFrequencySwitching.sankakuUntilHit(moveDistanceX, moveDistanceY);
	}

	void RobotAction::sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint forecastPoint)
	{
		if(FrameCoordinate::getCenterLine().x+3 < aPackCoordinate.x){
			moveToRightCenter(aMalletCoordinate, forecastPoint);
		}
		else if(aPackCoordinate.x < FrameCoordinate::getCenterLine().x-3){
			moveToLeftCenter(aMalletCoordinate, forecastPoint);
		}
		else{
			moveToCenter(aMalletCoordinate);
		}
	}

	void RobotAction::alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate)
	{
		double speed = mSpeedOfPack.getSpeed(); //0.1以下ならほとんど動いていない

		if(FrameCoordinate::getCenterLine().y + 70 < aPackCoordinate.y){
			if(aPackCoordinate.y < 370){
				if(mAlarmTimer.getOperatingTime() > 1.5){ //一定時間以上、自フィールドにパックがあるとき
					if(speed < 0.03){
						sankakuUntilHit(aMalletCoordinate, aPackCoordinate);
					}
					else{
						sankakuUntilHit(aMalletCoordinate, aForecastPackCoordinate);
					}
					sankakuCenterBack();
					mAlarmTimer.resetStartOperatingTime();
				}
			}
			else if(370 <= aPackCoordinate.y){
				if(mAlarmTimer.getOperatingTime() > 1.5){ //一定時間以上、自フィールドにパックがあるとき
					if(speed < 0.03){
						moveRightAngle(aMalletCoordinate, aPackCoordinate);
					}
					else{
						moveRightAngle(aMalletCoordinate, aForecastPackCoordinate);
					}
					//sankakuCenterBack() は不要
					mAlarmTimer.resetStartOperatingTime();
				}
			}
		}
		else{
			mAlarmTimer.resetStartOperatingTime();
		}
	}

	void RobotAction::alarmHitBackDefense(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate)
	{
		double speed = mSpeedOfPack.getSpeed(); //0.1以下ならほとんど動いていない

		if(FrameCoordinate::getCenterLine().y + 50 < aPackCoordinate.y){
			if(aPackCoordinate.y < 400){
				if(mAlarmTimer.getOperatingTime() > 2.0){ //一定時間以上、自フィールドにパックがあるとき
					if(speed < 0.01){
						sankakuUntilHit(aMalletCoordinate, aPackCoordinate);
						sankakuCenterBack();
						mAlarmTimer.resetStartOperatingTime();
					}
					/*
					else{
						sankakuUntilHit(aMalletCoordinate, aForecastPackCoordinate);
					}
					*/
					
				}
			}
			else if(400 <= aPackCoordinate.y){
				if(mAlarmTimer.getOperatingTime() > 2.0){ //一定時間以上、自フィールドにパックがあるとき
					if(speed < 0.01){
						moveRightAngle(aMalletCoordinate, aPackCoordinate);
					}
					/*
					else{
						moveRightAngle(aMalletCoordinate, aForecastPackCoordinate);
					}
					*/
				}
			}
		}
		else{
			mAlarmTimer.resetStartOperatingTime();
		}
	}

	void RobotAction::moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		CvPoint packCoordinate = aPackCoordinate;
		int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
		int moveDistanceY = abs(packCoordinate.y - aMalletCoordinate.y);

		mFrequencySwitching.sankakuRightAngle(moveDistanceX, moveDistanceY);
		mFrequencySwitching.sankakuReturnProcess();
	}
}  // namespace Strategy
