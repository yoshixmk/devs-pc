#include "StrategyTest.h"

namespace Test {
	StrategyTest::StrategyTest() {

	}

	void StrategyTest::packCoordinateTest()
	{
		std::cout << "!!!packCoordinate Test!!!" << std::endl;

		Hardware::Camera::renew();
		Strategy::PackCoordinate packCoordinate;
		while (1){
			Hardware::Camera::renew();
			std::cout << "X: " << packCoordinate.getCoordinate().x;
			std::cout << "  Y: " << packCoordinate.getCoordinate().y << std::endl;
			if (cv::waitKey(1) >= 0) {
				break;
			}
		}
		//	packCoordinate.getPreviousCoordinate();
	}

	void StrategyTest::malletCoordinateTest()
	{
		std::cout << "!!!malletCoordinate Test!!!" << std::endl;

		Hardware::Camera::renew();
		Strategy::MalletCoordinate malletCoordinate;
		while (1){
			Hardware::Camera::renew();
			std::cout << "X: " << malletCoordinate.getCoordinate().x;
			std::cout << "  Y: " << malletCoordinate.getCoordinate().y << std::endl;
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
		//std::cout << "!!!Locus Test!!!" << std::endl;
		//Hardware::Camera::renew();
		//Strategy::PackCoordinate packCoordinate;
		//Strategy::Locus locus;
		//while (1){
		//	Hardware::Camera::renew();
		//	CvPoint coordinate = packCoordinate.getCoordinate();
		//	CvPoint previousCoordinate = packCoordinate.getPreviousCoordinate();
		//	locus.calculateLocus(coordinate, previousCoordinate);
		//	double a_inclination = locus.getAInclination();
		//	double b_intercept = locus.getBIntercept();
		//	std::cout << "a: " << a_inclination << std::endl;
		//	std::cout << "b: " << b_intercept << std::endl;
		//	if (cv::waitKey(1) >= 0) {
		//		break;
		//	}
		//}
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
		frequencySwitchingX.setOutputInformation('A', 3);
		while (1){
			frequencySwitchingX.output();
		}
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

	void StrategyTest::robotActionTest()
	{
		std::cout << "!!!RobotAction Test!!!" << std::endl;
		/*CLEyeCameraInstance camera = CLEyeCreateCamera(CLEyeGetCameraUUID(0),
			CLEYE_COLOR_PROCESSED, CLEYE_VGA, 60);

		int width, height;
		CLEyeCameraGetFrameDimensions(camera, width, height);

		CLEyeSetCameraParameter(camera, CLEYE_GAIN, 5);
		CLEyeSetCameraParameter(camera, CLEYE_EXPOSURE, 511);
		CLEyeCameraStart(camera);

		IplImage* iplImage =
			cvCreateImage(cv::Size(width, height), IPL_DEPTH_8U, 4);
		cv::Mat iplMat = cv::Mat(iplImage);
		CLEyeCameraGetFrame(camera, (PBYTE)iplImage->imageData);

		cv::Mat image;
		cv::cvtColor(iplMat, image, CV_BGRA2BGR);*/

		/*CvCapture* mCvCapture0;
		mCvCapture0 = cvCreateCameraCapture(-1);
		if (mCvCapture0 == NULL){
			std::cout << "Camera Capture FAILED" << std::endl;
			exit(-1);
		}*/

		/*Hardware::Camera::renew();
		Strategy::MalletCoordinate malletCoordinate;
		Strategy::RobotAction robotAction;
		Hardware::Timer timer;
		double passed_time;
		while (1){
			Hardware::Camera::renew();
			robotAction.moveToCenter(malletCoordinate.getCoordinate());
			std::cout << malletCoordinate.getCoordinate().x << std::endl;

			passed_time = timer.getOperatingTime();
			std::cout << "time: " << passed_time << std::endl;

			if (cv::waitKey(1) >= 0) {
				break;
			}
		}*/
	}

}  // namespace Test
