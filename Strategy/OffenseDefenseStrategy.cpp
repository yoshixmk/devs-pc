#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void strongModeOD(LPVOID pParam)
{
	CvPoint malletNowC;
	CvPoint packNowC;
	CvPoint packPre0C;
	CvPoint packPre1C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction robotAction;
	SpeedOfPack speedOfPack;
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	bool hasSankakued = false;
	Hardware::Timer backTimer;
	robotAction.setCenterYLine(448);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		if(hasSankakued == false){
			packPre0C = packCoordinate.getPreviousCoordinate();
			packPre1C = packCoordinate.getPreviousCoordinate(1);
			if(packPre0C.y + 4 < packNowC.y){
				int speed = speedOfPack.getMomentSpeed();
				if(speed < 0.45){
					if(locus.calculateLocus(packNowC, packPre0C, 420) == true){	//軌跡検出
							forecastPoint = locus.getLocusCoordinate();
							robotAction.sankakuHitBack(malletNowC, forecastPoint);
							backTimer.setTimer(0.4);
							hasSankakued = true;
					}
					else{
						robotAction.moveToCenterDefense(malletNowC);	//中央に移動
					}
				}
				else{
					if(locus.calculateLocus(packNowC, packPre0C, 420) == true){	//軌跡検出
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
						//robotAction.moveToCenterDefense(malletNowC);	//中央に移動
						robotAction.moveToCenter(malletNowC);
					}
				}
			}
			else if(packNowC.y > 400){
				robotAction.moveToCenter(malletNowC);
			}
			else if(0 < packNowC.x && packNowC.x < 45 && 350 < packNowC.y && packNowC.y < 390){
				robotAction.sankakuUntilHit(packNowC, cvPoint(45, 350));
				hasSankakued = true;
			}
			else{
				robotAction.moveToCenter(malletNowC);	//中央に移動
			}
		}
		else if(hasSankakued == true){
			int distance = sqrt(pow(malletNowC.x-packNowC.x, 2.0)+pow(malletNowC.y-packNowC.y, 2.0));
			if(malletNowC.y < packNowC.y || distance < 5 || backTimer.getAlarm()){
				robotAction.sankakuCenterBack();
				hasSankakued = false;
			}
		}
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		if(locus.calculateLocus(packNowC, packPre1C, 390) == true){	//軌跡検出
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
	CvPoint packPre1C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotActionWeak robotAction;
	Locus locus;
	Hardware::Timer mTimer;
	mTimer.setTimer(20);
	MalletCoordinate malletCoordinate;
	PackCoordinate packCoordinate;

	bool hasSankakued = false;
	Hardware::Timer backTimer;
	robotAction.setCenterYLine(448);
	while(!mTimer.getAlarm()){
		Hardware::Camera::renew();
		malletNowC = malletCoordinate.getCoordinate();
		packNowC = packCoordinate.getCoordinate();
		if(hasSankakued == false){
			packPre0C = packCoordinate.getPreviousCoordinate();
			packPre1C = packCoordinate.getPreviousCoordinate(1);
			if(packPre0C.y + 4 < packNowC.y){
				if(atackCount < 1){
					if(locus.calculateLocus(packNowC, packPre0C, 420) == true){	//軌跡検出
						forecastPoint = locus.getLocusCoordinate();
						robotAction.sankakuHitBack(malletNowC, forecastPoint);
						backTimer.setTimer(0.5);
						atackCount++;
						hasSankakued = true;
					}
				}
				else{
					robotAction.moveToCenter(malletNowC);
				}
			}
			else if(packNowC.y > 360){
				robotAction.moveToCenter(malletNowC);
			}
			else if(0 < packNowC.x && packNowC.x < 45 && 350 < packNowC.y && packNowC.y < 390){
				robotAction.sankakuUntilHit(packNowC, cvPoint(45, 350));
				hasSankakued = true;
			}
			else{
				atackCount = 0;
				robotAction.moveToCenter(malletNowC);	//中央に移動
			}
		}
		else if(hasSankakued == true){
			int distance = sqrt(pow(malletNowC.x-packNowC.x, 2.0)+pow(malletNowC.y-packNowC.y, 2.0));
			if(malletNowC.y < packNowC.y || distance < 5 || backTimer.getAlarm()){
				robotAction.sankakuCenterBack();
				atackCount++;
				hasSankakued = false;
			}
		}
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		if(locus.calculateLocus(packNowC, packPre1C, 400) == true){	//軌跡検出
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
	hThread[0] = (HANDLE)_beginthread(strongModeOD, 0, NULL);	//スレッド１作成
	hThread[1] = (HANDLE)_beginthread(weakModeOD, 0, NULL);	//スレッド２作成

	//スレッド１、２終了待ち
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
		

	//}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
