#include "DefenseStrategy.h"

namespace Strategy {

//void DefenseStrategy::initialize() {
//}

void strongModeD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	Locus locus;
	while(1){
		malletNowC = cvPoint(11,22);//malletCoordinate.getCoordinate();
		packNowC = cvPoint(22,33);//packCoordinate.getCoordinate();
		packPre0C = cvPoint(33,44);//packCoordinate.getPreviousCoordinate();
		packPre2C = cvPoint(44,55);//packCoordinate.getPreviousCoordinate(2);
		if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.sideGuard(malletNowC, packNowC);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void weakModeD(LPVOID pParam)
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

void DefenseStrategy::execute()
{
	bool hasArrived = true; //�ړI�n�܂ňړ���=false, �ړ�����=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModeD, 0, NULL);	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthread(weakModeD, 0, NULL);	//�X���b�h�Q�쐬

	//�X���b�h�P�A�Q�I���҂�
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
}

//void DefenseStrategy::terminate() {
//}
}  // namespace Strategy
