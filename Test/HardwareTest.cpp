#include "HardwareTest.h"

namespace Test {
/* シグナル受信/処理 */
void HardwareTest::signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	exit(0);
}

HardwareTest::HardwareTest() {
	//gpioCfgClock(4, 0, 100);
	//if (gpioInitialise() < 0) {
	//	std::cout << "pigpio initialisation failed." << std::endl;
	//} else {
	//	std::cout << "pigpio initialised okay." << std::endl;
	//}

	//if (signal(SIGINT, &signalHandler) == SIG_ERR) {
	//	std::cout << "I could not set up signal. finished" << std::endl;
	//	gpioTerminate();
	//	exit(1);
	//}
}

HardwareTest::~HardwareTest() {
	//gpioTerminate();
}
//
void HardwareTest::timerTest() {
	std::cout << "!!!Timer Test!!!" << std::endl; // Timer Test start!

	Hardware::Timer timer;

	timer.setTimer(3.501);
	while (!timer.getAlarm());
	/*//while(!timer.getAlarm()){
	 if(timer.getAlarm()){
	 std::cout << "getAlarm() retun Bool OK." << std::endl;
	 }
	 else{
	 std::cout << "getAlarm() retun Bool NG." << std::endl;
	 }
	 //}*/
}

//void HardwareTest::raspberryPiSignalTest() {
//	Hardware::RaspberryPiSignal raspberryPiSignal(8);
//
//	std::cout << raspberryPiSignal.readLevel() << std::endl;
//}
//

void HardwareTest::cameraTest() {
	std::cout << "Camera_test" << std::endl;
	Hardware::Camera camera;

	cvNamedWindow("RobotSide", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HumanSide", CV_WINDOW_AUTOSIZE);

	while (1) {
		Hardware::Camera::renew();
		cvShowImage("RobotSide", camera.getRobotSideImage());
		cvShowImage("HumanSide", camera.getHumanSideImage());
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void HardwareTest::serialTest(){
	std::cout << "Serial_test" << std::endl;
	Hardware::Serial serial;
	
	while(1){
		unsigned char buf[] = { 50, 0, 'A', 100, 100, 100, 100, 100, 100 };
		int i = 0;
		while (1){
			serial.serialWrite((char*)buf, 4);
			if (buf[0] == 255){
				break;
			}

			if (buf[0] < 255){
				buf[0] += 1;
			}
			if (buf[1] < 255){
				buf[1] += 1;
			}
			if (buf[2] == 'A'){
				buf[2] = 'B';
			}
			else if (buf[2] == 'B'){
				buf[2] = 'C';
			}
			else if (buf[2] == 'C'){
				buf[2] = 'D';
			}
			else if (buf[2] == 'D'){
				buf[2] = 'A';
			}
		}
	}
}

}  // namespace Test
