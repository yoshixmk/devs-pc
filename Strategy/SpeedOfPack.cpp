#include "SpeedOfPack.h"

namespace Strategy
{

SpeedOfPack::SpeedOfPack()
{
	for(int i=0; i<9; i++){
		//mPackCoordinate.getCoordinate();
	}

	//移動平均のために、初期値を代入。
	for(int i=0; i<10; i++){
		mSpeed[i] = 0;
	}
}

//通常のスピード取得。getSpeed
double SpeedOfPack::getSpeed()
{
	CvPoint packNowC = mPackCoordinate.getCoordinate();
	CvPoint packPreC = mPackCoordinate.getPreviousCoordinate(9);

	//座標距離1あたりの距離
	const double M_PER_PIX = 699.0 / 243.0 / 1000.0;

	double distance = sqrt(pow(packNowC.x - packPreC.x, 2.0) + pow(packNowC.y - packPreC.y, 2.0));

	for(int i=0; i<sizeof(mSpeed)/sizeof(mSpeed[0])-1; i++){
		mSpeed[i+1] = mSpeed[i];
	}

	//ウィンドウ無し
	mSpeed[0] = M_PER_PIX * distance / 0.33; //デフォ0.34、合わせてみて0.33
	//ウィンドウあり
	//double mSpeed = distance / 0.07;

	double sum = 0.0;
	for(int i=0; i<sizeof(mSpeed)/sizeof(mSpeed[0]); i++){
		sum += mSpeed[i];
	}

	double aveSpeed = sum / (double)(sizeof(mSpeed)/sizeof(mSpeed[0]));
	//m/s -> km/h
	//aveSpeed = aveSpeed * 3600 /1000;

	//ブレがあり、止まっていても速度が出てしまう場合
	/*if(aveSpeed < 3){
		aveSpeed = 0;
	}*/

	return aveSpeed;
}

//最新の2枚を使用。通常はgetSpeedだが、プレイヤー側の手元で判断したい場合に使用する。
double SpeedOfPack::getMomentSpeed()
{
	CvPoint packNowC = mPackCoordinate.getCoordinate();
	CvPoint packPreC = mPackCoordinate.getPreviousCoordinate(0);

	//座標距離1あたりの距離
	const double M_PER_PIX = 699.0 / 243.0 / 1000.0;

	double distance = sqrt(pow(packNowC.x - packPreC.x, 2.0) + pow(packNowC.y - packPreC.y, 2.0));

	for(int i=0; i<sizeof(mSpeed)/sizeof(mSpeed[0])-1; i++){
		mSpeed[i+1] = mSpeed[i];
	}

	//ウィンドウ無し
	double speed = mSpeed[0] = M_PER_PIX * distance / 0.33; //デフォ0.34、合わせてみて0.33
	//ウィンドウあり
	//double mSpeed = distance / 0.07;

	return speed;
}
}  // namespace Strategy
