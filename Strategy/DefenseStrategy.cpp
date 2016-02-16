#include "DefenseStrategy.h"

namespace Strategy {

void strongModeD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre1C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	robotAction.setCenterYLine(446);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre1C = packCoordinate.getPreviousCoordinate(1);
		if( (packPre0C.y + 4 < packNowC.y) && packNowC.y < 400){
			if(locus.calculateLocus(packNowC, packPre0C, 420) == true){	//�O�Ռ��o
				forecastPoint = locus.getLocusCoordinate();
				if(forecastPoint.x > FrameCoordinate::getRobotGoalLeft().x && FrameCoordinate::getRobotGoalRight().x > forecastPoint.x){
					robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
				
				else if(forecastPoint.x < FrameCoordinate::getRobotGoalLeft().x){
					 forecastPoint.x = FrameCoordinate::getRobotGoalLeft().x; 
					 robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
				else{
					forecastPoint.x = FrameCoordinate::getRobotGoalRight().x;
					robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
			}
			else{
				robotAction.moveToCenterDefense(malletNowC);	//�����Ɉړ�
				//robotAction.moveToCenter(malletNowC);
			}
		}
		else{
			robotAction.moveToCenterDefense(malletNowC);	//�����Ɉړ�
		}
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre1C, 390) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.alarmHitBack(malletNowC, packNowC, forecastPoint);
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
	CvPoint packPre1C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotActionWeak robotAction;
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	robotAction.setCenterYLine(446);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre1C = packCoordinate.getPreviousCoordinate(1);
		if( (packPre0C.y + 4 < packNowC.y) && packNowC.y < 400){
			if(locus.calculateLocus(packNowC, packPre0C, 420) == true){	//�O�Ռ��o
				forecastPoint = locus.getLocusCoordinate();
				if(forecastPoint.x > FrameCoordinate::getRobotGoalLeft().x && FrameCoordinate::getRobotGoalRight().x > forecastPoint.x){
					robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
				
				else if(forecastPoint.x < FrameCoordinate::getRobotGoalLeft().x){
					 forecastPoint.x = FrameCoordinate::getRobotGoalLeft().x; 
					 robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
				else{
					forecastPoint.x = FrameCoordinate::getRobotGoalRight().x;
					robotAction.sankakuDefense(malletNowC, forecastPoint);
				}
			}
			else{
				//robotAction.moveToCenterDefense(malletNowC);	//�����Ɉړ�
				robotAction.moveToCenter(malletNowC);
			}
		}
		else{
			robotAction.moveToCenterDefense(malletNowC);	//�����Ɉړ�
		}
		//���Ԃ����Ă���ꍇ�A�ł��ɂ����B�����͕K�v�Ȃ�
		if(locus.calculateLocus(packNowC, packPre1C, 390) == true){	//�O�Ռ��o
			forecastPoint = locus.getLocusCoordinate();
			robotAction.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}
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
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//�n���h���N���[�Y
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
}

//void DefenseStrategy::terminate() {
//}
}  // namespace Strategy
