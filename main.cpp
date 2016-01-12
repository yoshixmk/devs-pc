#include "Test/HardwareTest.h"
//#include "Test/ColorTest.h"
//#include "Test/StrategyTest.h"
//#include "Test/UITest.h"
//#include "Test/ShowWindowTest.h"
#include <stdio.h>

int main() {
	
	/*printf("Use the following keys to change camera parameters:\n"
		"\t'1' - select camera 1\n"
		"\t'2' - select camera 2\n"
		"\t'g' - select gain parameter\n"
		"\t'e' - select exposure parameter\n"
		"\t'z' - select zoom parameter\n"
		"\t'r' - select rotation parameter\n"
		"\t'+' - increment selected parameter\n"
		"\t'-' - decrement selected parameter\n");
	// The <ESC> key will exit the program
	CLEyeCameraCapture *pCam = NULL;
	int param = -1, key;
	while((key = cvWaitKey(0)) != 0x1b)
	{
		switch(key)
		{
			case 'g':	case 'G':	printf("Parameter Gain\n");		param = CLEYE_GAIN;		break;
			case 'e':	case 'E':	printf("Parameter Exposure\n");	param = CLEYE_EXPOSURE;	break;
			case 'z':	case 'Z':	printf("Parameter Zoom\n");		param = CLEYE_ZOOM;		break;
			case 'r':	case 'R':	printf("Parameter Rotation\n");	param = CLEYE_ROTATION;	break;
			case '1':				printf("Selected camera 1\n");	pCam = cam[0];			break;
			case '2':				printf("Selected camera 2\n");	pCam = cam[1];			break;
			case '+':	if(pCam)	pCam->IncrementCameraParameter(param);		break;
			case '-':	if(pCam)	pCam->DecrementCameraParameter(param);		break;
		}
	}

	for(int i = 0; i < numCams; i++)
	{
		printf("Stopping capture on camera %d\n", i+1);
		cam[i]->StopCapture();
		delete cam[i];
	}*/

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
	hardwareTest.cameraTest();
	//hardwareTest.serialTest();

	//Test::ColorTest colorTest;
	//colorTest.twoImageSynthesisTest();
	//colorTest.hockeyTableMaskingTest();
//	colorTest.robotSideHockeyTableMaskingTest();
	//colorTest.perspectiveTransformationTest();
	//colorTest.colorExtractionTest();

	//Test::StrategyTest strategyTest;
	//strategyTest.anomalyDetectionTest();
	//strategyTest.packCoordinateTest();
//	strategyTest.malletCoordinateTest();
//	strategyTest.frameCoordinateTest();
	//strategyTest.locusTest();
	//strategyTest.frequencySwitching_X_Test();
	//strategyTest.frequencySwitching_Y_Test();
	//strategyTest.robotActionTest();

//	Test::UITest uiTest;
//	uiTest.intelligentTest();
//	uiTest.soundTest();

	//Test::ShowWindowTest showWindowTest;
	//showWindowTest.windowTest();
	//showWindowTest.drawingTest();
//	showWindowTest.manageTest();
	return 0;
}
