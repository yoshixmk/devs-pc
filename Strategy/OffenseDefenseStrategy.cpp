#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	CvPoint packNowC = mPackCoordinate.getCoordinate();
	CvPoint packPreC = mPackCoordinate.getPreviousCoordinate();
	CvPoint malletNowC = mMalletCoordinate.getCoordinate();
	CvPoint centerLine = FrameCoordinate::getCenterLine();

	//ほぼ動きが変わらない場合は、無視する。
	if( abs(packNowC.x - packPreC.x) > 1 || abs(packNowC.y - packPreC.y) > 1){
		//ロボットからプレイヤーにパックを打ち返したとき。パックの静止はabs()ですでに無視してある
		if(packNowC.y - packPreC.y < -2){
			//中央復帰
			mRobotAction.moveToCenter(malletNowC);
			//}
		}
		else if(centerLine.y - 100 < packNowC.y && centerLine.y - 100 > packPreC.y){
			//yLineを340で予測
			if(mLocus.calculateLocus(packNowC, packPreC, 340) == true){
				CvPoint forecastPoint = mLocus.getLocusCoordinate();
				mRobotAction.moveToHitBack(malletNowC, forecastPoint);
			}
		}
	}


}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
