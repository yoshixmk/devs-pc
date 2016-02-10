#include "RobotActionWeak.h"

namespace Strategy {
	RobotActionWeak::RobotActionWeak()
	{
		//default value
		mCenterYLine = 410;
	}

	void RobotActionWeak::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::moveToCenterDefense(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = 432;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::guardCenter(CvPoint aMalletCoordinate)
	{
		int moveDistanceX = FrameCoordinate::getCenterLine().x - aMalletCoordinate.x;
		int moveDistanceY = 426 - aMalletCoordinate.y;
		mFrequencySwitching.sankakuCenterProcess(moveDistanceX, moveDistanceY);
	}

	void RobotActionWeak::moveToRightCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 35;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::moveToRightCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 35;
		waitingPosition.y = mCenterYLine;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::moveToLeftCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 35;
		waitingPosition.y = mCenterYLine + 1; //画像が少し斜めのため
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::moveToLeftCenter(CvPoint aMalletCoordinate, CvPoint forecastPoint)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 35;
		waitingPosition.y = mCenterYLine + 1; //画像が少し斜めのため
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotActionWeak::moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition)
	{
		int xMargin = 3;
		int yMargin = 5;
		int maxSpeedUp = 2000;

		//X
		if(aWaitingPosition.x - xMargin < aMalletCoordinate.x && aMalletCoordinate.x < aWaitingPosition.x + xMargin){//定位置付近
			mFrequencyManualX.setOutputInformation(0);
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
				mFrequencyManualY.setOutputInformation('D', 400);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('A', 400);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
			mMoveingTimer.resetStartOperatingTime();
		}
		else if(aMalletCoordinate.x <= aWaitingPosition.x - xMargin){ //BまたはCの方向
			if (aMalletCoordinate.x < aWaitingPosition.x - 40){
				//ゴールから遠いと速くする。10ms以上時間が経過していればに+100加速
				int nowMaxSpeed = 400 + (int)(mMoveingTimer.getOperatingTime() * 100) * 100;
				int frequencyX = mFrequencyManualX.getFrequencyX();
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
				if(mFrequencyManualX.getTargetDirection() == 'C'){
					mFrequencyManualX.setOutputInformation('C', frequencyX);
				}
				else{
					mFrequencyManualX.setOutputInformation('C', 400);
					mMoveingTimer.resetStartOperatingTime();
				}
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x - 10){
				//ゴール近辺ならモータの速度を落とす
				mFrequencyManualX.setOutputInformation('C', 300);
				mMoveingTimer.resetStartOperatingTime();
			}
			else if (aMalletCoordinate.x <= aWaitingPosition.x){
				//ゴールに少し近づいてきたら速度を落とす
				mFrequencyManualX.setOutputInformation('C', 0.200);
				mMoveingTimer.resetStartOperatingTime();
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
				mFrequencyManualY.setOutputInformation('C', 400);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('B', 400);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		else if(aWaitingPosition.x + xMargin <= aMalletCoordinate.x){ //AまたはDの方向
			if (aMalletCoordinate.x < aWaitingPosition.x + 10){
				//ゴールに少し近づいてきたら速度を落とす
				mFrequencyManualX.setOutputInformation('D', 100);
				mMoveingTimer.resetStartOperatingTime();
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x + 40){
				//ゴール近辺ならモータの速度を落とす
				mFrequencyManualX.setOutputInformation('D', 300);
				mMoveingTimer.resetStartOperatingTime();
			}
			else{
				//ゴールから遠いと速くする。10ms以上時間が経過していればに+100加速
				int nowMaxSpeed = 400 + (int)(mMoveingTimer.getOperatingTime() * 100) * 100;
				int frequencyX = mFrequencyManualX.getFrequencyX();
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
				if(mFrequencyManualX.getTargetDirection() == 'D'){
					mFrequencyManualX.setOutputInformation('D', frequencyX);
				}
				else{
					mFrequencyManualX.setOutputInformation('D', 400);
					mMoveingTimer.resetStartOperatingTime();
				}
			}
			//Y
			if(aMalletCoordinate.y < aWaitingPosition.y - yMargin){ //定位置付近でないなら
				mFrequencyManualY.setOutputInformation('D', 400);
			}
			else if(aWaitingPosition.y + yMargin < aMalletCoordinate.y){
				mFrequencyManualY.setOutputInformation('A', 400);
			}
			else{
				mFrequencyManualY.setOutputInformation(0);
			}
		}
		mFrequencyManual.output();
	}

	bool RobotActionWeak::moveToHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
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

	void RobotActionWeak::sankakuHitBack(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		//リミットスイッチに当たってしまわないように補正
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

	void RobotActionWeak::sankakuDefense(CvPoint aMalletCoordinate, CvPoint aForecastPackCoordinate)
	{
		//リミットスイッチに当たってしまわないように補正
		CvPoint forecastPackCoordinate = aForecastPackCoordinate;
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		mFrequencySwitching.sankakuDefense(moveDistance);
	}

	void RobotActionWeak::sankakuCenterBack()
	{
		mFrequencySwitching.sankakuReturnProcess();
	}

	void RobotActionWeak::sankakuUntilHit(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		//リミットスイッチに当たってしまわないように補正
		CvPoint packCoordinate = aPackCoordinate;
		if(packCoordinate.x < 33){
			packCoordinate.x = 33;
		}
		if(packCoordinate.x > 290){
			packCoordinate.x = 290;
		}
		int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
		int moveDistanceY = aMalletCoordinate.y - packCoordinate.y;
		if(moveDistanceY < 0){
			moveDistanceY = 0;
		}
		mFrequencySwitching.sankakuUntilHit(moveDistanceX, moveDistanceY);
	}

	void RobotActionWeak::sideGuard(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
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

	void RobotActionWeak::alarmHitBack(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate)
	{
		double speed = mSpeedOfPack.getSpeed(); //0.1以下ならほとんど動いていない

		if(FrameCoordinate::getCenterLine().y + 50 < aPackCoordinate.y){
			if(aPackCoordinate.y < 400){
				if(mAlarmTimer.getOperatingTime() > 1.0){ //一定時間以上、自フィールドにパックがあるとき
					//std::cout << "alarm Hit Back" << std::endl;
					if(speed < 0.1){
						sankakuUntilHit(aMalletCoordinate, aPackCoordinate);
					}
					else{
						sankakuUntilHit(aMalletCoordinate, aForecastPackCoordinate);
					}
					sankakuCenterBack();
					mAlarmTimer.resetStartOperatingTime();
				}
			}
			else if(400 <= aPackCoordinate.y){
				if(mAlarmTimer.getOperatingTime() > 1.0){ //一定時間以上、自フィールドにパックがあるとき
					//std::cout << "alarm Hit Back" << std::endl;
					if(speed < 0.1){
						moveRightAngle(aMalletCoordinate, aPackCoordinate);
					}
					else{
						moveRightAngle(aMalletCoordinate, aForecastPackCoordinate);
					}
				}
			}
		}
		else{
			mAlarmTimer.resetStartOperatingTime();
		}
	}

	void RobotActionWeak::alarmHitBackDefence(CvPoint aMalletCoordinate, CvPoint aPackCoordinate, CvPoint aForecastPackCoordinate)
	{
		double speed = mSpeedOfPack.getSpeed(); //0.1以下ならほとんど動いていない

		if(FrameCoordinate::getCenterLine().y + 50 < aPackCoordinate.y){
			if(aPackCoordinate.y < 400){
				if(mAlarmTimer.getOperatingTime() > 1.0){ //一定時間以上、自フィールドにパックがあるとき
					//std::cout << "alarm Hit Back" << std::endl;
					if(speed < 0.1){
						sankakuUntilHit(aMalletCoordinate, aPackCoordinate);
					}
					else{
						sankakuUntilHit(aMalletCoordinate, aForecastPackCoordinate);
					}
					sankakuCenterBack();
					mAlarmTimer.resetStartOperatingTime();
				}
			}
			else if(400 <= aPackCoordinate.y){
				if(mAlarmTimer.getOperatingTime() > 1.0){ //一定時間以上、自フィールドにパックがあるとき
					//std::cout << "alarm Hit Back" << std::endl;
					if(speed < 0.1){
						moveRightAngle(aMalletCoordinate, aPackCoordinate);
					}
					else{
						moveRightAngle(aMalletCoordinate, aForecastPackCoordinate);
					}
				}
			}
		}
		else{
			mAlarmTimer.resetStartOperatingTime();
		}
	}

	void RobotActionWeak::moveRightAngle(CvPoint aMalletCoordinate, CvPoint aPackCoordinate)
	{
		if(mFrequencyManualX.getFrequencyX() == 0 && mFrequencyManualY.getFrequencyY() == 0){
			//リミットスイッチに当たってしまわないように補正
			CvPoint packCoordinate = aPackCoordinate;
			int moveDistanceX = packCoordinate.x - aMalletCoordinate.x;
			int moveDistanceY = packCoordinate.y - aMalletCoordinate.y;
			mFrequencySwitching.sankakuRightAngle(moveDistanceX, moveDistanceY);
			mFrequencySwitching.sankakuReturnProcess();
		}
		else{
			moveToCenter(aMalletCoordinate);
		}
	}
}  // namespace Strategy
