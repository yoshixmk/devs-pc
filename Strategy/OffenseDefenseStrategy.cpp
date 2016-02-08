#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void strongModeOD(LPVOID pParam)
{
	int atackCount = 0;
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

	bool hasSankakued = false;
	Hardware::Timer backTimer;
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		if(hasSankakued == false){
			packPre0C = packCoordinate.getPreviousCoordinate();
			packPre2C = packCoordinate.getPreviousCoordinate(2);
			if( (packPre0C.y + 5 < packNowC.y) && atackCount < 1){
				if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
					forecastPoint = locus.getLocusCoordinate();
					robotAction.sankakuHitBack(malletNowC, forecastPoint);
					backTimer.setTimer(0.5);
					atackCount++;
					hasSankakued = true;
				}
			}
			else{
				atackCount = 0;
				robotAction.moveToCenter(malletNowC);	//�����Ɉړ�
			}
		}
		else if(hasSankakued == true){
			int distance = sqrt(pow(malletNowC.x-packNowC.x, 2.0)+pow(malletNowC.y-packNowC.y, 2.0));
			if(malletNowC.y < packNowC.y || distance < 5 || backTimer.getAlarm()){
				robotAction.sankakuCenterBack();
				hasSankakued = false;
			}
		}

		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}

		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void weakModeOD(LPVOID pParam)
{
	int atackCount = 0;
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotActionWeak robotAction;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre2C = packCoordinate.getPreviousCoordinate(2);
		if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//�O�Ռ��o
				forecastPoint = locus.getLocusCoordinate();
				robotAction.sankakuHitBack(malletNowC, forecastPoint);
				robotAction.sankakuCenterBack();
				atackCount++;
			}
		}
		else{
			atackCount = 0;
			robotAction.moveToCenter(malletNowC);	//�����Ɉړ�
		}
			
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void OffenseDefenseStrategy::execute()
{
	std::cout << "OffenseDeffense Strategy!!" << std::endl;

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
	//}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
