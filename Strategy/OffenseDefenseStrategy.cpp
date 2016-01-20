#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	CvPoint packNowC = mPackCoordinate.getCoordinate();
	CvPoint packPreC = mPackCoordinate.getPreviousCoordinate();
	CvPoint malletNowC = mMalletCoordinate.getCoordinate();

	//ほぼ動きが変わらない場合は、無視する。
	if( abs(packNowC.x - packPreC.x) > 1 || abs(packNowC.y - packPreC.y) > 1){
		//ロボットからプレイヤーにパックを打ち返したとき。パックの静止はabs()で無視
		if(packNowC.y - packPreC.y < -2){
			//yLineを330で予測
			//if(mLocus.calculateLocus(packNowCorrdinate, packPreCorrdinate, 330) == true){
			//	CvPoint forecastPoint = mLocus.getLocusCoordinate();
			//中央復帰
			mRobotAction.moveToCenter(malletNowC);
			//}
		}
		else if()

	}


}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
