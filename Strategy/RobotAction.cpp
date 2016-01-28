#include "RobotAction.h"

namespace Strategy {

	void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
	{
		CvPoint waiting_position;
		waiting_position.x = (FrameCoordinate::getRobotGoalLeft().x + FrameCoordinate::getRobotGoalRight().x) / 2;
		waiting_position.y = 405;

		if (aMalletCoordinate.x < waiting_position.x - 40){
			//ゴールから遠いと速くする
			//mFrequencySwitchingX.setOutputInformation('C', 0.700);//640ms以上で3500Hz台形
			mFrequencyManualX.setOutputInformation('C', 300);
		}
		else if (aMalletCoordinate.x < waiting_position.x - 10){
			//ゴール近辺ならモータの速度を落とす
			//mFrequencySwitchingX.setOutputInformation('C', 0.350);
			mFrequencyManualX.setOutputInformation('C', 200);
		}
		else if (aMalletCoordinate.x <= waiting_position.x - 3){
			//ゴールに少し近づいてきたら速度を落とす
			mFrequencyManualX.setOutputInformation('C', 0.200);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 3){
			//-3 ~ 3 の範囲は停止
			//mFrequencySwitchingX.stop();
			mFrequencyManualX.setOutputInformation(0);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 10){
			//ゴールに少し近づいてきたら速度を落とす
			//mFrequencySwitchingX.setOutputInformation('D', 0.200);
			mFrequencyManualX.setOutputInformation('D', 100);
		}
		else if (aMalletCoordinate.x < waiting_position.x + 40){
			//ゴール近辺ならモータの速度を落とす
			//mFrequencySwitchingX.setOutputInformation('D', 0.350);
			mFrequencyManualX.setOutputInformation('D', 200);
		}
		else{
			//mFrequencySwitchingX.setOutputInformation('D', 0.700);//640ms以上で3500Hz台形
			mFrequencyManualX.setOutputInformation('D', 300);
		}

		if(aMalletCoordinate.y < waiting_position.y){ //定位置より上側なら
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
}  // namespace Strategy
