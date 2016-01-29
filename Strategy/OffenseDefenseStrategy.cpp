#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	bool hasArrived = true; //–Ú“I’n‚Ü‚ÅˆÚ“®’†=false, ˆÚ“®Š®—¹=true

	CvPoint forecastPoint = cvPoint(0, 0);
	int atackCount = 0;
	while(1){
		Hardware::Camera::renew();
		CvPoint malletNowC = mMalletCoordinate.getCoordinate();
		CvPoint packNowC = mPackCoordinate.getCoordinate();
		CvPoint packPre0C = mPackCoordinate.getPreviousCoordinate();
		CvPoint packPre1C = mPackCoordinate.getPreviousCoordinate(1);
		CvPoint packPre2C = mPackCoordinate.getPreviousCoordinate(2);
		CvPoint packPre3C = mPackCoordinate.getPreviousCoordinate(3);
			
		//IplImage* extractMallet = hockeyTableMasking.mask();
			//colorExtractionMallet.extractRobotSideHockeyTable();
			
		//int yLineTrigger = 160;
		//if( (packPre1C.y < yLineTrigger && yLineTrigger + 1 <= packNowC.y) && atackCount < 1 ){
		if( (packPre1C.y + 4 < packNowC.y) && atackCount < 2 ){
			if(mLocus.calculateLocus(packNowC, packPre1C, 360) == true){	//‹OÕŒŸo
				forecastPoint = mLocus.getLocusCoordinate();
				mRobotAction.sankakuHitBack(malletNowC, forecastPoint);
				std::cout << "sankaku!! 0" << std::endl;
				atackCount++;
			}
			else if(mLocus.calculateLocus(packNowC, packPre1C, 360) == true){
				mRobotAction.sankakuHitBack(malletNowC, forecastPoint);
				forecastPoint = mLocus.getLocusCoordinate();
				std::cout << "sankaku!! 1" << std::endl;
			}
			else if(mLocus.calculateLocus(packNowC, packPre1C, 360) == true){
				mRobotAction.sankakuHitBack(malletNowC, forecastPoint);
				forecastPoint = mLocus.getLocusCoordinate();
				std::cout << "sankaku!! 2" << std::endl;
			}
		}
		else{
			atackCount = 0;
			mRobotAction.moveToCenter(malletNowC);	//’†‰›‚ÉˆÚ“®
		}
		//cvCircle(extractMallet, forecastPoint, 5, cvScalar(255,255,0));
		//cvShowImage("ColorExtractionRS", extractMallet);
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
