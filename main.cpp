#include "Test/HardwareTest.h"
#include "Test/ColorTest.h"
#include "Test/StrategyTest.h"
//#include "Test/UITest.h"
//#include "Test/ShowWindowTest.h"
#include <stdio.h>

int main() {
	Hardware::Camera::initialize();

	Test::HardwareTest hardwareTest;
	//hardwareTest.timerTest();
	//hardware_test.raspberryPiSignalTest();
	//hardware_test.photoelectricSensor();
	//hardware_test.photomicrosensor();
	//hardware_test.limitSwitch();
	//hardware_test.proximitySensor();
	//hardwareTest.pushSwitchTest();
	//hardwareTest.moterDriverTest();
	//hardwareTest.speakerTest();
//	hardwareTest.bgmSignalTest();
	//hardwareTest.cameraTest();
	//hardwareTest.serialTest();

	Test::ColorTest colorTest;
	//colorTest.twoImageSynthesisTest();
	//colorTest.hockeyTableMaskingTest();
	//colorTest.robotSideHockeyTableMaskingTest();
	//colorTest.perspectiveTransformationTest();
	//colorTest.nonFlipTwoImageSynthesisTest();
	//colorTest.colorExtractionTest();

	Test::StrategyTest strategyTest;
	//strategyTest.packCoordinateTest();
	//strategyTest.malletCoordinateTest();
	//strategyTest.frameCoordinateTest();
	//strategyTest.locusTest();
	//strategyTest.frequencySwitching_X_Test();
	//strategyTest.frequencySwitching_Y_Test();
	//strategyTest.robotActionTest();
	//strategyTest.frequencyManualTest();
	//strategyTest.frequencyManualXTest();
	//strategyTest.frequencyManualYTest();
	strategyTest.speedOfPackTest();

//	Test::UITest uiTest;
//	uiTest.intelligentTest();
//	uiTest.soundTest();

	//Test::ShowWindowTest showWindowTest;
	//showWindowTest.windowTest();
	//showWindowTest.drawingTest();
//	showWindowTest.manageTest();
	return 0;
}
