#include "DefenseStrategy.h"

namespace Strategy {

//void DefenseStrategy::initialize() {
//}

//void strongModeD(LPVOID pParam)
//{
//	CvPoint malletNowC;
//	CvPoint packNowC;
//	CvPoint packPre0C;
//	CvPoint forecastPoint;
//	RobotAction robotAction;
//	MalletCoordinate malletCoordinate;
//	PackCoordinate packCoordinate;
//	Locus locus;
//	Hardware::Timer mTimer;
//	mTimer.setTimer(20);
//	while(!mTimer.getAlarm()){
//		Hardware::Camera::renew();
//		malletNowC = malletCoordinate.getCoordinate();
//		packNowC = packCoordinate.getCoordinate();
//		packPre0C = packCoordinate.getPreviousCoordinate(0);
//		if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
//			forecastPoint = locus.getLocusCoordinate();
//			robotAction.sideGuard(malletNowC, packNowC,forecastPoint);
//		}
//
//		
//		if (cv::waitKey(1) >= 0) {
//			break;
//		}
//	}
//}

void strongModeD(LPVOID pParam)
{
	int atackCount = 0;
	int goalhasi = 40;
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre2C = packCoordinate.getPreviousCoordinate(30);
		//if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
		if( (packPre0C.y + 4 < packNowC.y) && packNowC.y < 400){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
				forecastPoint = locus.getLocusCoordinate();
				if((forecastPoint.x > FrameCoordinate::getCenterLine().x - goalhasi) && (FrameCoordinate::getCenterLine().x + goalhasi > forecastPoint.x)){
					robotAction.sankakuDefence(malletNowC, forecastPoint);
					//robotAction.sankakuCenterBack();
					//atackCount++;
					printf("kiseki");
				}
				
				else if(forecastPoint.x < FrameCoordinate::getCenterLine().x - goalhasi){
					 forecastPoint.x = FrameCoordinate::getCenterLine().x - goalhasi; 
					 robotAction.sankakuDefence(malletNowC, forecastPoint);
					 //atackCount++;
					 printf("��");
				}
				else{
					forecastPoint.x = FrameCoordinate::getCenterLine().x + goalhasi; 
					robotAction.sankakuDefence(malletNowC, forecastPoint);
					//atackCount++;
					printf("�E");
				}
				
			}
		}
		else if(malletNowC.y-150 > packNowC.y){
			//atackCount = 0;
			robotAction.moveToCenterDefence(malletNowC);	//�����Ɉړ�
			printf("center");
		}
		printf(" a\n");	
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//�O�Ռ��o
			//atackCount = 0;
			forecastPoint = locus.getLocusCoordinate();
			robotAction.alarmHitBackDefence(malletNowC, packNowC, forecastPoint);
			//printf("alarm\n");
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
	RobotActionWeak robotAction;
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		robotAction.sideGuard(malletNowC, packNowC);
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void DefenseStrategy::execute()
{
	std::cout << "Defense Strategy!!" << std::endl;

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
