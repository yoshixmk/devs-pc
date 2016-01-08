#include "Test/HardwareTest.h"
//#include "Test/ColorTest.h"
//#include "Test/StrategyTest.h"
//#include "Test/UITest.h"
//#include "Test/ShowWindowTest.h"
#include "CLEyeMulticam/CLEyeCameraCapture.h"
#include <stdio.h>

int main() {
	printf("hello world\n");
	printf("hello world\n");
	
	CLEyeCameraCapture *cam[2] = { NULL };
	srand(GetTickCount());
	// Query for number of connected cameras
	int numCams = CLEyeGetCameraCount();
	if(numCams == 0)
	{
		printf("No PS3Eye cameras detected\n");
		return -1;
	}
	printf("Found %d cameras\n", numCams);
	for(int i = 0; i < numCams; i++)
	{
		char windowName[64];
		// Query unique camera uuid
		GUID guid = CLEyeGetCameraUUID(i);
		printf("Camera %d GUID: [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]\n", 
						i+1, guid.Data1, guid.Data2, guid.Data3,
						guid.Data4[0], guid.Data4[1], guid.Data4[2],
						guid.Data4[3], guid.Data4[4], guid.Data4[5],
						guid.Data4[6], guid.Data4[7]);
		sprintf(windowName, "Camera Window %d", i+1);
		// Create camera capture object
		// Randomize resolution and color mode
		cam[i] = new CLEyeCameraCapture(windowName, guid, rand()<(RAND_MAX>>1) ? CLEYE_COLOR_PROCESSED : CLEYE_MONO_PROCESSED, 
														rand()<(RAND_MAX>>1) ? CLEYE_VGA : CLEYE_QVGA, 30);
		printf("Starting capture on camera %d\n", i+1);
		cam[i]->StartCapture();
	}
	printf("Use the following keys to change camera parameters:\n"
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
	}

	//Test::HardwareTest hardwareTest;
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
