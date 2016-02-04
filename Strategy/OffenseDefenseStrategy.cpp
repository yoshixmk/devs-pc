#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void strongModeOD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	Locus locus;
	while(1){
		malletNowC = cvPoint(110,220);//malletCoordinate.getCoordinate();
		packNowC = cvPoint(220,330);//packCoordinate.getCoordinate();
		packPre0C = cvPoint(303,404);//packCoordinate.getPreviousCoordinate();
		packPre2C = cvPoint(404,404);//packCoordinate.getPreviousCoordinate(2);
		if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.sankakuHitBack(malletNowC, forecastPoint);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void weakModeOD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	Locus locus;
	while(1){
		malletNowC = cvPoint(110,220);//malletCoordinate.getCoordinate();
		packNowC = cvPoint(220,330);//packCoordinate.getCoordinate();
		packPre0C = cvPoint(303,404);//packCoordinate.getPreviousCoordinate();
		packPre2C = cvPoint(404,404);//packCoordinate.getPreviousCoordinate(2);
		if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.sankakuHitBack(malletNowC, forecastPoint);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void OffenseDefenseStrategy::execute()
{
	bool hasArrived = true; //�ړI�n�܂ňړ���=false, �ړ�����=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModeOD, 0, NULL);	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthread(weakModeOD, 0, NULL);	//�X���b�h�Q�쐬

	//�X���b�h�P�A�Q�I���҂�
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
	//MalletCoordinate malletCoordinate;	//�}���b�g�̈ʒu
	//Locus locus;							//�O��
	//PackCoordinate packCoordinate;

	
		//Hardware::Camera::renew();

		
		
		/*if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
				forecastPoint = locus.getLocusCoordinate();
				//robotActionS.sankakuHitBack(malletNowC, forecastPoint);
				robotActionW.sankakuHitBack(malletNowC, forecastPoint);
				//std::cout << "sankaku Hit Back" << std::endl;
				//robotActionS.sankakuCenterBack();
				robotActionW.sankakuCenterBack();
				//std::cout << "sankaku Center Back" << std::endl;
				atackCount++;
			}
		}
		else{
			atackCount = 0;
			//robotActionS.moveToCenter(malletNowC);	//�����Ɉړ�
			robotActionW.moveToCenter(malletNowC);	//�����Ɉړ�
			//std::cout << "Move To Center" << std::endl;
		}*/
			
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		/*if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			//robotActionS.alarmHitBack(malletNowC, packNowC, forecastPoint);
			robotActionW.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}*/


	//}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
