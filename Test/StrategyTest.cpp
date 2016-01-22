#include "StrategyTest.h"

namespace Test {
	StrategyTest::StrategyTest() {

	}

	void StrategyTest::packCoordinateTest()
	{
		std::cout << "!!!packCoordinate Test!!!" << std::endl;

		Strategy::PackCoordinate packCoordinate;
		
		//Hardware::Timer timer;
		//double passedTime;
		Color::ColorExtraction colorExtractionPack;
		colorExtractionPack.setPackHSV();
		while (1){
			//passedTime = 0;
			//for(int i=0; i<100; i++){
			//timer.resetStartOperatingTime();

			Hardware::Camera::renew();
			CvPoint packNowC = packCoordinate.getCoordinate();
			//std::cout << "X: " << packNowC.x;
			//std::cout << "  Y: " << packNowC.y << std::endl;
			IplImage* extractPack = colorExtractionPack.extractHockeyTable();
			std::ostringstream os;
			os << "Pack X:" << packNowC.x;
			std::string number = os.str();
			int len = number.length();
			char* fname = new char[len+1];
			memcpy(fname, number.c_str(), len+1);
			cvPutText(extractPack, fname, cvPoint(10,40), &cvFont(2.0), cvScalar(0,255,0));
			std::ostringstream os2;
			os2 << "Pack Y:" << packNowC.y;
			number = os2.str();
			len = number.length();
			fname = new char[len+1];
			memcpy(fname, number.c_str(), len+1);
			cvPutText(extractPack, fname, cvPoint(10,80), &cvFont(2.0), cvScalar(0,255,0));

			cvShowImage("ColorExtractionRS", extractPack);
			if (cv::waitKey(1) >= 0) {
				break;
			}

			//passedTime += timer.getOperatingTime();
			//}
			//std::cout << passedTime/100 << std::endl;

		}
		//	packCoordinate.getPreviousCoordinate();
	}

	void StrategyTest::malletCoordinateTest()
	{
		std::cout << "!!!malletCoordinate Test!!!" << std::endl;

		Strategy::MalletCoordinate malletCoordinate;

		Color::ColorExtraction colorExtractionMallet;
		colorExtractionMallet.setMalletHSV();
		while (1){
			Hardware::Camera::renew();

			CvPoint malletNowC = malletCoordinate.getCoordinate();
			//std::cout << "X: " << malletCoordinate.getCoordinate().x;
			//std::cout << "  Y: " << malletCoordinate.getCoordinate().y << std::endl;

			IplImage* extractMallet = colorExtractionMallet.extractRobotSideHockeyTable();
			std::ostringstream os;
			os << "Pack X:" << malletNowC.x;
			std::string number = os.str();
			int len = number.length();
			char* fname = new char[len+1];
			memcpy(fname, number.c_str(), len+1);
			cvPutText(extractMallet, fname, cvPoint(10,40), &cvFont(2.0), cvScalar(0,255,0));
			std::ostringstream os2;
			os2 << "Pack Y:" << malletNowC.y;
			number = os2.str();
			len = number.length();
			fname = new char[len+1];
			memcpy(fname, number.c_str(), len+1);
			cvPutText(extractMallet, fname, cvPoint(10,80), &cvFont(2.0), cvScalar(0,255,0));

			cvShowImage("ColorExtractionRS", extractMallet);

			if (cv::waitKey(1) >= 0) {
				break;
			}
		}
	}

	void StrategyTest::frameCoordinateTest()
	{
		std::cout << "!!!frameCoordinate Test!!!" << std::endl;
		Strategy::FrameCoordinate frameCoordinate;
		std::cout << "X: " << frameCoordinate.getUpperLeftF().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getUpperLeftF().y << std::endl;

		std::cout << "X: " << frameCoordinate.getLowerLeftF().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getLowerLeftF().y << std::endl;

		std::cout << "X: " << frameCoordinate.getUpperRightF().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getUpperRightF().y << std::endl;

		std::cout << "X: " << frameCoordinate.getLowerRightF().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getLowerRightF().y << std::endl;

		std::cout << "X: " << frameCoordinate.getUpperLeftG().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getUpperLeftG().y << std::endl;

		std::cout << "X: " << frameCoordinate.getLowerLeftG().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getLowerLeftG().y << std::endl;

		std::cout << "X: " << frameCoordinate.getUpperRightG().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getUpperRightG().y << std::endl;

		std::cout << "X: " << frameCoordinate.getLowerRightG().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getLowerRightG().y << std::endl;

		std::cout << "X: " << frameCoordinate.getRobotGoalLeft().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getRobotGoalLeft().y << std::endl;

		std::cout << "X: " << frameCoordinate.getRobotGoalRight().x << std::endl;
		std::cout << "Y: " << frameCoordinate.getRobotGoalRight().y << std::endl;
	}

	void StrategyTest::locusTest()
	{
		std::cout << "!!!Locus Test!!!" << std::endl;
		Hardware::Camera::renew();
		Strategy::PackCoordinate packCoordinate;
		Strategy::Locus locus;
		Color::HockeyTableMasking hockeyTableMasking;
		IplImage* locusMasking;
		int yLine = 350;
		while (1){
			Hardware::Camera::renew();
			CvPoint coordinate = packCoordinate.getCoordinate();
			CvPoint previousCoordinate = packCoordinate.getPreviousCoordinate();
			
			locusMasking = hockeyTableMasking.mask();
			if( abs(coordinate.x - previousCoordinate.x) > 1){
				if(locus.calculateLocus(coordinate, previousCoordinate, yLine) == true){
					CvPoint forecastPoint = locus.getLocusCoordinate();

					cvCircle(locusMasking, forecastPoint, 10, cvScalar(0, 0, 255));
				}
			}

			cvShowImage("Locas", locusMasking);

			if (cv::waitKey(1) >= 0) {
				break;
			}
		}
	}

	void StrategyTest::frequencySwitchingTest()
	{
		//std::cout << "!!!FrequencySwitching Test!!!" << std::endl;
		//Strategy::FrequencySwitching frequencySwitching('Y');
		//frequencySwitching.setOutputInformation('D', 5);
		//while (1){
		//	frequencySwitching.output();
		//	if (cv::waitKey(1) >= 0) {
		//		break;
		//	}
		//}
	}

	void StrategyTest::frequencySwitching_X_Test()
	{
		std::cout << "!!!FrequencySwitching X Test!!!" << std::endl;
		Strategy::FrequencySwitchingX frequencySwitchingX;
		/*frequencySwitchingX.setOutputInformation('A', 3);
		while (1){
			frequencySwitchingX.output();
		}*/
		frequencySwitchingX.sankakuProcess(100);
	}

	void StrategyTest::frequencySwitching_Y_Test()
	{
		std::cout << "!!!FrequencySwitching Y Test!!!" << std::endl;

		Strategy::FrequencySwitchingX frequencySwitchingX;
		Strategy::FrequencySwitchingY frequencySwitchingY;
		
		frequencySwitchingX.setOutputInformation('A', 2);
		frequencySwitchingY.setOutputInformation('B', 3); //To check 'B' is priority
		while (1){
			frequencySwitchingX.output();
			frequencySwitchingY.output();
		}
	}

	void StrategyTest::frequency_X_Test()
	{
		//std::cout << "!!!Frequency X Test!!!" << std::endl;
		//Strategy::FrequencyX frequencyX;

		//Hardware::Timer timer;
		//timer.setTimer(5);

		//while (1){
		//	if (!timer.getAlarm()){
		//		//			frequencyX.output1000('R');
		//		frequencyX.output100('R');
		//	}
		//	else{
		//		break;
		//	}
		//	if (cv::waitKey(1) >= 0) {
		//		break;
		//	}
		//}
	}

	void StrategyTest::frequency_Y_Test()
	{
		//std::cout << "!!!Frequency Y Test!!!" << std::endl;
		//Strategy::FrequencyY frequencyY;

		//Hardware::Timer timer;
		//timer.setTimer(5);

		//while (1){
		//	if (!timer.getAlarm()){
		//		//			frequencyY.output1000('U');
		//		frequencyY.output313('D');
		//	}
		//	else{
		//		break;
		//	}
		//	if (cv::waitKey(1) >= 0) {
		//		break;
		//	}
		//}
	}

	void StrategyTest::frequencyManualTest()
	{
		std::cout << "!!!FrequencyManual Test!!!" << std::endl;

		Hardware::Camera::renew();

		Strategy::FrequencyManual frequencyManual;
		frequencyManual.setOutputInformation('A', 1000, 500);
	}

	void StrategyTest::frequencyManualXTest()
	{
		std::cout << "!!!FrequencyManualX Test!!!" << std::endl;

		Hardware::Camera::renew();

		Strategy::FrequencyManual frequencyManual;
		frequencyManual.setOutputInformation('B', 900, 400);

	}

	void StrategyTest::frequencyManualYTest()
	{
		std::cout << "!!!FrequencyManualY Test!!!" << std::endl;

		Hardware::Camera::renew();

		Strategy::FrequencyManual frequencyManual;
		frequencyManual.setOutputInformation('C', 800, 300);
	}

	void StrategyTest::robotActionTest()
	{
		std::cout << "!!!Robot Action Test!!!" << std::endl;

		Hardware::Camera::renew();

		Strategy::RobotAction robotAction;
		Strategy::MalletCoordinate malletCoordinate;
		Strategy::Locus locus;
		Strategy::PackCoordinate packCoordinate;
		robotAction.moveToCenter(malletCoordinate.getCoordinate());

		/*if(locus.calculateLocus(packCoordinate.getCoordinate(), packCoordinate.getPreviousCoordinate(), 340) == true){
			CvPoint forecastPoint = locus.getLocusCoordinate();
			robotAction.moveToHitBack(malletCoordinate.getCoordinate(), forecastPoint);
		}*/
	}
	void StrategyTest::offenseDeffenseStrategyTest()
	{
		std::cout << "!!!OffenseDeffenseStrategy Test!!!" << std::endl;

		Hardware::Camera::renew();

		Strategy::OffenseDefenseStrategy offenseDefenseStrategy;

		offenseDefenseStrategy.execute();
	}
	
	void StrategyTest::speedOfPackTest()
	{
		std::cout << "!!!SpeedOfPackTest Test!!!" << std::endl;

		Strategy::SpeedOfPack speedOfPack;

		while(1){
			Hardware::Camera::renew();
			double speed = speedOfPack.getSpeed();

			if(speed < 100){
				std::cout << speed << std::endl;
			}

		}
	}
}  // namespace Test
