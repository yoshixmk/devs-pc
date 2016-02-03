#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	bool hasArrived = true; //目的地まで移動中=false, 移動完了=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;
	RobotAction robotActionS;
	RobotActionWeak robotActionW;
	MalletCoordinate malletCoordinate;	//マレットの位置
	Locus locus;							//軌跡
	PackCoordinate packCoordinate;

	while(1){
		Hardware::Camera::renew();
		CvPoint malletNowC = malletCoordinate.getCoordinate();
		CvPoint packNowC =packCoordinate.getCoordinate();
		CvPoint packPre0C = packCoordinate.getPreviousCoordinate();
		CvPoint packPre2C = packCoordinate.getPreviousCoordinate(2);

		if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//軌跡検出
				forecastPoint = locus.getLocusCoordinate();
				robotActionS.sankakuHitBack(malletNowC, forecastPoint);
				robotActionW.sankakuHitBack(malletNowC, forecastPoint);
				robotActionS.sankakuCenterBack();
				robotActionW.sankakuCenterBack();
				atackCount++;
			}
		}
		else{
			atackCount = 0;
			robotActionS.moveToCenter(malletNowC);	//中央に移動
			robotActionW.moveToCenter(malletNowC);	//中央に移動
		}
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//軌跡検出
			forecastPoint = locus.getLocusCoordinate();
			robotActionS.alarmHitBack(malletNowC, packNowC, forecastPoint);
			robotActionW.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}

		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
