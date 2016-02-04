#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void strongModeOD(LPVOID pParam)
{
	CvPoint mMalletNowC;
	CvPoint mPackNowC;
	CvPoint mPackPre0C;
	CvPoint mPackPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction mRobotActionS;
	RobotActionWeak mRobotActionW;
	Locus mLocus;
	while(1){
		mMalletNowC = cvPoint(11,22);//malletCoordinate.getCoordinate();
		mPackNowC = cvPoint(22,33);//packCoordinate.getCoordinate();
		mPackPre0C = cvPoint(33,44);//packCoordinate.getPreviousCoordinate();
		mPackPre2C = cvPoint(44,55);//packCoordinate.getPreviousCoordinate(2);
		if(mLocus.calculateLocus(mPackNowC, mPackPre0C, 360) == true){	//軌跡検出
			forecastPoint = mLocus.getLocusCoordinate();
			mRobotActionS.sankakuHitBack(mMalletNowC, forecastPoint);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void weakModeOD(LPVOID pParam)
{
	CvPoint mMalletNowC;
	CvPoint mPackNowC;
	CvPoint mPackPre0C;
	CvPoint mPackPre2C;
	CvPoint forecastPoint = cvPoint(0, 0);
	RobotAction mRobotActionS;
	RobotActionWeak mRobotActionW;
	Locus mLocus;
	while(1){
		mMalletNowC = cvPoint(110,220);//malletCoordinate.getCoordinate();
		mPackNowC = cvPoint(220,330);//packCoordinate.getCoordinate();
		mPackPre0C = cvPoint(303,404);//packCoordinate.getPreviousCoordinate();
		mPackPre2C = cvPoint(404,404);//packCoordinate.getPreviousCoordinate(2);
		if(mLocus.calculateLocus(mPackNowC, mPackPre0C, 360) == true){	//軌跡検出
			forecastPoint = mLocus.getLocusCoordinate();
			mRobotActionW.sankakuHitBack(mMalletNowC, forecastPoint);
		}
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void OffenseDefenseStrategy::execute()
{
	bool hasArrived = true; //目的地まで移動中=false, 移動完了=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;

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
	//MalletCoordinate malletCoordinate;	//マレットの位置
	//Locus locus;							//軌跡
	//PackCoordinate packCoordinate;

	
		//Hardware::Camera::renew();

		
		
		/*if( (packPre0C.y + 4 < packNowC.y) && atackCount < 1){
			if(locus.calculateLocus(packNowC, packPre0C, 360) == true){	//軌跡検出
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
			//robotActionS.moveToCenter(malletNowC);	//中央に移動
			robotActionW.moveToCenter(malletNowC);	//中央に移動
			//std::cout << "Move To Center" << std::endl;
		}*/
			
		//時間が来ている場合、打ちにいく。条件は必要ない
		/*if(locus.calculateLocus(packNowC, packPre2C, 360) == true){	//軌跡検出
			forecastPoint = locus.getLocusCoordinate();
			//robotActionS.alarmHitBack(malletNowC, packNowC, forecastPoint);
			robotActionW.alarmHitBack(malletNowC, packNowC, forecastPoint);
		}*/


	//}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
