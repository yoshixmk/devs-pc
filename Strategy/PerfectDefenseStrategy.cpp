#include "PerfectDefenseStrategy.h"

namespace Strategy {

void strongModePD(LPVOID pParam)
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
			if(locus.calculateLocus(packNowC, packPre0C, 390) == true){	//�O�Ռ��o
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
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}


void weakModePD(LPVOID pParam)
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
			if(locus.calculateLocus(packNowC, packPre0C, 390) == true){	//�O�Ռ��o
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
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void PerfectDefenseStrategy::execute()
{
	std::cout << "Perfect Defense Strategy!!" << std::endl;

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModePD, 0, NULL);	//�X���b�h�P�쐬
	hThread[1] = (HANDLE)_beginthread(weakModePD, 0, NULL);	//�X���b�h�Q�쐬
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
