#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x;
		waitingPosition.y = 423;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}

	void RobotAction::moveToRightCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x + 25;
		waitingPosition.y = 423;
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}
	void RobotAction::moveToLeftCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waitingPosition;
		waitingPosition.x = FrameCoordinate::getCenterLine().x - 25;
		waitingPosition.y = 423 + 1; //画像が少し斜めのため
		moveToWaitingPosition(aMalletCoordinate, waitingPosition);
	}
	void RobotAction::moveToWaitingPosition(CvPoint aMalletCoordinate, CvPoint aWaitingPosition)
	{
		int xMargin = 3;
		int yMargin = 5;
		//X
		if(aWaitingPosition.x - xMargin < aMalletCoordinate.x && aMalletCoordinate.x < aWaitingPosition.x + xMargin){//定位置付近
			//-3 ～ 3 の範囲は停止
			//mFrequencySwitchingX.stop();
			mFrequencyManualX.setOutputInformation(0);
			
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
		else if(aMalletCoordinate.x <= aWaitingPosition.x - xMargin){ //BまたはCの方向
			if (aMalletCoordinate.x < aWaitingPosition.x - 40){
				//ゴールから遠いと速くする
				//mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms以上で3500Hz台形
				mFrequencyManualX.setOutputInformation('C', 400);
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x - 10){
				//ゴール近辺ならモータの速度を落とす
				//mFrequencySwitchingX.setOutputInformation('C', 0.350);
				mFrequencyManualX.setOutputInformation('C', 300);
			}
			else if (aMalletCoordinate.x <= aWaitingPosition.x){
				//ゴールに少し近づいてきたら速度を落とす
				mFrequencyManualX.setOutputInformation('C', 0.200);
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
				//mFrequencySwitchingX.setOutputInformation('D', 0.200);
				mFrequencyManualX.setOutputInformation('D', 100);
			}
			else if (aMalletCoordinate.x < aWaitingPosition.x + 40){
				//ゴール近辺ならモータの速度を落とす
				//mFrequencySwitchingX.setOutputInformation('D', 0.350);
				mFrequencyManualX.setOutputInformation('D', 300);
			}
			else{
				//mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms以上で3500Hz台形
				mFrequencyManualX.setOutputInformation('D', 400);
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
		if(forecastPackCoordinate.x < 60){
			forecastPackCoordinate.x = 60;
		}
		if(forecastPackCoordinate.x > 270){
			forecastPackCoordinate.x = 270;
		}
		int moveDistance = forecastPackCoordinate.x - aMalletCoordinate.x;

		printf("moveDistance:%d\n", moveDistance);
		//moveDistanceはパックが
		//右に飛んでくる予想の場合＋、左に飛んでくる予想の場合－
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

	void RobotAction::sankakuCenterBack()
	{
		mFrequencySwitching.sankakuReturnProcess();
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
}  // namespace Strategy
