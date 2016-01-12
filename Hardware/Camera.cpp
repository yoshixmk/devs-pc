#include "Camera.h"

namespace Hardware
{
IplImage* Camera::mHumanSideImage;
IplImage* Camera::mRobotSideImage;
CvCapture* Camera::mCvCapture0;
CvCapture* Camera::mCvCapture1;
int Camera::mWidth;
int Camera::mHeight;
CLEyeCameraCapture* Camera::cam[2];

Camera::Camera(int aWidth, int aHeight)
{
	cam[0] = NULL;
	cam[1] = NULL;

	srand(GetTickCount());
	// Query for number of connected cameras
	mNumCamera = CLEyeGetCameraCount();
	if(mNumCamera == 0)
	{
		printf("No PS3Eye cameras detected\n");
		exit(-1);
	}
	printf("Found %d cameras\n", mNumCamera);

	for(int i = 0; i < mNumCamera; i++)
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
		cam[i] = new CLEyeCameraCapture(guid, rand()<(RAND_MAX>>1) ? CLEYE_COLOR_PROCESSED : CLEYE_MONO_PROCESSED, 
														rand()<(RAND_MAX>>1) ? CLEYE_VGA : CLEYE_QVGA, 60);
		// Create camera capture object
		printf("Starting capture on camera %d\n", i+1);
		cam[i]->initCamera();
			
		printf("start ok.", i+1);
	}
	//additional settings 
	cam[0]->setPerspectiveTransform(0, 180);//pack
	cam[1]->setPerspectiveTransform(10, -180);//mallet
	cam[0]->setVerticalFlip(true);
	cam[0]->setHorizontalFlip(true);

	for(int i = 0; i < mNumCamera; i++)
	{
		cam[i]->StartCapture();
	}

    renew();
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
	//printf("renew affter\n");
}

}  // namespace Hardware
