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

	//�قړ������ς��Ȃ��ꍇ�́A��������B
	if( abs(packNowC.x - packPreC.x) > 1 || abs(packNowC.y - packPreC.y) > 1){
		//���{�b�g����v���C���[�Ƀp�b�N��ł��Ԃ����Ƃ��B�p�b�N�̐Î~��abs()�ł��łɖ������Ă���
		if(packNowC.y - packPreC.y < -2){
			//�������A
			mRobotAction.moveToCenter(malletNowC);
			//}
		}
		else if(centerLine.y - 100 < packNowC.y && centerLine.y - 100 > packPreC.y){
			//yLine��340�ŗ\��
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
