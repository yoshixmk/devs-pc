#include "DefenseStrategy.h"

namespace Strategy {

//void DefenseStrategy::initialize() {
//}

void strongModeD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	RobotAction robotAction;
	Locus locus;
	while(1){
		malletNowC = cvPoint(11,22);//malletCoordinate.getCoordinate();
		packNowC = cvPoint(22,33);//packCoordinate.getCoordinate();
		robotAction.sideGuard(malletNowC, packNowC);
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void weakModeD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	RobotActionWeak robotAction;
	Locus locus;
	while(1){
		malletNowC = cvPoint(110,220);//malletCoordinate.getCoordinate();
		packNowC = cvPoint(220,330);//packCoordinate.getCoordinate();
		robotAction.sideGuard(malletNowC, packNowC);
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void DefenseStrategy::execute()
{
	std::cout << "Defense Strategy!!" << std::endl;

	bool hasArrived = true; //�ړI�n�܂ňړ���=false, �ړ�����=true
	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;
	mTimer.setTimer(3);

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModeD, 0, NULL);	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthread(weakModeD, 0, NULL);	//�X���b�h�Q�쐬

	while(!mTimer.getAlarm()){
		//�X���b�h�P�A�Q�I���҂�
		//WaitForMultipleObjects(2,hThread,TRUE,INFINITE);
	}

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
}

//void DefenseStrategy::terminate() {
//}
}  // namespace Strategy
