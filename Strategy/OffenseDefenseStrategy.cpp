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
	mTimer.setTimer(30);
	//while(1){
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre2C = packCoordinate.getPreviousCoordinate(30);
		if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//軌跡検出
				forecastPoint = locus.getLocusCoordinate();
				//robotActionS.sankakuHitBack(malletNowC, forecastPoint);
				robotAction.sankakuHitBack(malletNowC, forecastPoint);
				//std::cout << "sankaku Hit Back" << std::endl;
				//robotActionS.sankakuCenterBack();
				robotAction.sankakuCenterBack();
				//std::cout << "sankaku Center Back" << std::endl;
				atackCount++;
			}
		}
		else{
			atackCount = 0;
			//robotActionS.moveToCenter(malletNowC);	//中央に移動
			robotAction.moveToCenter(malletNowC);	//中央に移動
			//std::cout << "Move To Center" << std::endl;
		}
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//軌跡検出
			forecastPoint = locus.getLocusCoordinate();
			//robotActionS.alarmHitBack(malletNowC, packNowC, forecastPoint);
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
	mTimer.setTimer(30);
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	//while(1){
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		packPre0C = packCoordinate.getPreviousCoordinate();
		packPre2C = packCoordinate.getPreviousCoordinate(30);
		if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//軌跡検出
				forecastPoint = locus.getLocusCoordinate();
				//robotActionS.sankakuHitBack(malletNowC, forecastPoint);
				robotAction.sankakuHitBack(malletNowC, forecastPoint);
				//std::cout << "sankaku Hit Back" << std::endl;
				//robotActionS.sankakuCenterBack();
				robotAction.sankakuCenterBack();
				//std::cout << "sankaku Center Back" << std::endl;
				atackCount++;
			}
		}
		else{
			atackCount = 0;
			//robotActionS.moveToCenter(malletNowC);	//中央に移動
			robotAction.moveToCenter(malletNowC);	//中央に移動
			//std::cout << "Move To Center" << std::endl;
		}
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//軌跡検出
			forecastPoint = locus.getLocusCoordinate();
			//robotActionS.alarmHitBack(malletNowC, packNowC, forecastPoint);
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
	//bool hasArrived = true; //目的地まで移動中=false, 移動完了=true

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModeOD, 0, NULL);	//スレッド１作成
	hThread[1] = (HANDLE)_beginthread(weakModeOD, 0, NULL);	//スレッド２作成

	//スレッド１、２終了待ち
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
		

	//}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
