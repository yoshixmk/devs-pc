#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	CvPoint packNowC = mPackCoordinate.getCoordinate();
	CvPoint packPreC = mPackCoordinate.getPreviousCoordinate();
	CvPoint malletNowC = mMalletCoordinate.getCoordinate();

	//�قړ������ς��Ȃ��ꍇ�́A��������B
	if( abs(packNowC.x - packPreC.x) > 1 || abs(packNowC.y - packPreC.y) > 1){
		//���{�b�g����v���C���[�Ƀp�b�N��ł��Ԃ����Ƃ��B�p�b�N�̐Î~��abs()�Ŗ���
		if(packNowC.y - packPreC.y < -2){
			//yLine��330�ŗ\��
			//if(mLocus.calculateLocus(packNowCorrdinate, packPreCorrdinate, 330) == true){
			//	CvPoint forecastPoint = mLocus.getLocusCoordinate();
			//�������A
			mRobotAction.moveToCenter(malletNowC);
			//}
		}
		else if()

	}


}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
