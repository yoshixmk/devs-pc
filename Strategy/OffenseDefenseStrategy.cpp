#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	bool hasArrived = true; //�ړI�n�܂ňړ���=false, �ړ�����=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;
	RobotAction robotActionS;
	RobotActionWeak robotActionW;
	MalletCoordinate malletCoordinate;	//�}���b�g�̈ʒu
	Locus locus;							//�O��
	PackCoordinate packCoordinate;

	while(1){
		Hardware::Camera::renew();
		CvPoint malletNowC = malletCoordinate.getCoordinate();
		CvPoint packNowC =packCoordinate.getCoordinate();
		CvPoint packPre0C = packCoordinate.getPreviousCoordinate();
		CvPoint packPre2C = packCoordinate.getPreviousCoordinate(2);

		if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
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
			robotActionS.moveToCenter(malletNowC);	//�����Ɉړ�
			robotActionW.moveToCenter(malletNowC);	//�����Ɉړ�
		}
			
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//�O�Ռ��o
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
