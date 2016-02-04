#include "DefenseStrategy.h"

namespace Strategy {

//void DefenseStrategy::initialize() {
//}

void strongModeD(LPVOID pParam)
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

void weakModeD(LPVOID pParam)
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

void DefenseStrategy::execute()
{
	bool hasArrived = true; //目的地まで移動中=false, 移動完了=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;

	HANDLE	hThread[2];
	hMutex = CreateMutex(NULL,FALSE,NULL);
	Hardware::Serial::setMutex(&hMutex);
	hThread[0] = (HANDLE)_beginthread(strongModeD, 0, NULL);	//スレッド１作成
	hThread[1] = (HANDLE)_beginthread(weakModeD, 0, NULL);	//スレッド２作成

	//スレッド１、２終了待ち
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);

	//ハンドルクローズ
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	CloseHandle(hMutex);
}

//void DefenseStrategy::terminate() {
//}
}  // namespace Strategy
