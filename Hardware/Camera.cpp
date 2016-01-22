#include "Camera.h"

namespace Hardware
{
IplImage* Camera::mHumanSideImage;
IplImage* Camera::mRobotSideImage;
CvCapture* Camera::mCvCapture0;
CvCapture* Camera::mCvCapture1;
int Camera::mWidth;
int Camera::mHeight;
int Camera::mNumCamera;
CLEyeCameraCapture* Camera::cam[2];

void Camera::initialize(int aWidth, int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;

	cam[0] = NULL;
	cam[1] = NULL;

	srand(GetTickCount());
	// Query for number of connected cameras
	mNumCamera = CLEyeGetCameraCount();
	if(mNumCamera == 0)
	{
		printf("No PS3Eye cameras detected\n");
		exit(1);
	}
	/*ese if(mNumCamera == 1){

	}*/

	printf("Found %d cameras\n", mNumCamera);

	for(int i = 0; i < mNumCamera; i++)
	{
		// Query unique camera uuid
		GUID guid = CLEyeGetCameraUUID(i);
			
		/*printf("Camera %d GUID: [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]\n", 
						i+1, guid.Data1, guid.Data2, guid.Data3,
						guid.Data4[0], guid.Data4[1], guid.Data4[2],
						guid.Data4[3], guid.Data4[4], guid.Data4[5],
						guid.Data4[6], guid.Data4[7]);*/
		// Create camera capture object
		// Randomize resolution and color mode
		// exchange camera by UUID if Upside down
		if(guid.Data1 == 0xe6e7718e){
			cam[0] = new CLEyeCameraCapture(guid, rand()<(RAND_MAX>>1) ? CLEYE_COLOR_PROCESSED : CLEYE_MONO_PROCESSED, 
														rand()<(RAND_MAX>>1) ? CLEYE_VGA : CLEYE_QVGA, 60);
			// Create camera capture object
			std::cout << "Starting capture on Human Side camera" << i+1 << ". ";
			cam[0]->initCamera();
		}
		else if(guid.Data1 == 0x91cbacac){
			cam[1] = new CLEyeCameraCapture(guid, rand()<(RAND_MAX>>1) ? CLEYE_COLOR_PROCESSED : CLEYE_MONO_PROCESSED, 
														rand()<(RAND_MAX>>1) ? CLEYE_VGA : CLEYE_QVGA, 60);
			// Create camera capture object
			std::cout << "Starting capture on Robot Side camera" << i+1 << ". ";
			cam[1]->initCamera();
		}
		else{
			printf("いつものPS3Eyeではありません。\nFrom Camera.cpp\n");
			exit(1);
		}
		printf("start ok.\n", i+1);
	}

	//additional settings 
	cam[0]->setPerspectiveTransform(0, 180);//pack
	cam[1]->setPerspectiveTransform(0, -180);//mallet
	cam[0]->setVerticalFlip(true);
	cam[0]->setHorizontalFlip(true);

	for(int i = 0; i < mNumCamera; i++)
	{
		cam[i]->StartCapture();
	}

	//カメラの起動のため、何度か撮っておく
	for(int i=0; i<5; i++){
		renew();
	}
}

void Camera::setSize(int aWidth, int aHeight)
{
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FRAME_HEIGHT,aHeight);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FRAME_HEIGHT,aHeight);
	mWidth = aWidth;
	mHeight = aHeight;
}

int Camera::getWidth()
{
	return mWidth;
}

int Camera::getHeight()
{
	return mHeight;
}

IplImage* Camera::getRobotSideImage()
{
	return mRobotSideImage;
}

IplImage* Camera::getHumanSideImage()
{
	return mHumanSideImage;
}

void Camera::renew()
{
	cam[0]->run();
	cam[1]->run();
	mRobotSideImage = cam[0]->getCameraImage();
	mHumanSideImage = cam[1]->getCameraImage();
}

}  // namespace Hardware
