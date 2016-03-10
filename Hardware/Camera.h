#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

//#include <pigpio.h>
#include "../CLEye/opencv.hpp"
#include <iostream>
#include "../CLEyeMulticam/CLEyeCameraCapture.h"

namespace Hardware
{
class Camera
{
private:
	static IplImage* mRobotSideImage;
	static IplImage* mHumanSideImage;
	static CvCapture* mCvCapture0;
	static CvCapture* mCvCapture1;
	static int mWidth;
	static int mHeight;
	static int mNumCamera;
	static CLEyeCameraCapture *cam[2];
	static HANDLE hMutex; //ミューテックスのハンドル

public:
	//Camera(int aWidth=320, int aHeight=240);
	static void initialize(int aWidth=320, int aHeight=240);
	static void finalize();
	static void setSize(int aWidth=320, int aHeight=240);
	static int getWidth();
	static int getHeight();
	static void renew();
	static IplImage* getRobotSideImage();
	static IplImage* getHumanSideImage();
	static void setMutex(HANDLE* aMutex);
};

}  // namespace Hardware
#endif
