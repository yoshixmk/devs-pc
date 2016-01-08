//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This file is part of CL-EyeMulticam SDK
//
// C++ CLEyeMulticamTest Sample Application
//
// For updates and file downloads go to: http://codelaboratories.com/research/view/cl-eye-muticamera-sdk
//
// Copyright 2008-2012 (c) Code Laboratories, Inc. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

double GetRandomNormalized()
{
	return (double)(rand()-(RAND_MAX>>1))/(double)(RAND_MAX>>1);
}

// Sample camera capture class
class CLEyeCameraCapture
{
	CHAR _windowName[256];
	GUID _cameraGUID;
	CLEyeCameraInstance _cam;
	CLEyeCameraColorMode _mode;
	CLEyeCameraResolution _resolution;
	float _fps;
	HANDLE _hThread;
	bool _running;
public:
	CLEyeCameraCapture(LPSTR windowName, GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps) :
		_cameraGUID(cameraGUID), _cam(NULL), _mode(mode), _resolution(resolution), _fps(fps), _running(false)
	{
		strcpy(_windowName, windowName);
	}
	bool StartCapture()
	{
		_running = true;
		cvNamedWindow(_windowName, CV_WINDOW_AUTOSIZE);
		// Start CLEye image capture thread
		_hThread = CreateThread(NULL, 0, &CLEyeCameraCapture::CaptureThread, this, 0, 0);
		if(_hThread == NULL)
		{
			MessageBox(NULL,"Could not create capture thread","CLEyeMulticamTest", MB_ICONEXCLAMATION);
			return false;
		}
		return true;
	}
	void StopCapture()
	{
		if(!_running)	return;
		_running = false;
		WaitForSingleObject(_hThread, 1000);
		cvDestroyWindow(_windowName);
	}
	void IncrementCameraParameter(int param)
	{
		if(!_cam)	return;
		printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
		CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param)+10);
	}
	void DecrementCameraParameter(int param)
	{
		if(!_cam)	return;
		printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
		CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param)-10);
	}
	void Run()
	{
		int w, h;
		IplImage *pCapImage;
		PBYTE pCapBuffer = NULL;
		// Create camera instance
		_mode = CLEYE_COLOR_PROCESSED;
		_fps = 60;
		_resolution = CLEYE_QVGA;
		_cam = CLEyeCreateCamera(_cameraGUID, _mode, _resolution, _fps);
		if(_cam == NULL)		return;
		// Get camera frame dimensions
		CLEyeCameraGetFrameDimensions(_cam, w, h);
		// Depending on color mode chosen, create the appropriate OpenCV image
		//if(_mode == CLEYE_COLOR_PROCESSED || _mode == CLEYE_COLOR_RAW)
			pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);
		//else
			//pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);

		// Set some camera parameters
		CLEyeSetCameraParameter(_cam, CLEYE_GAIN, 50);
		CLEyeSetCameraParameter(_cam, CLEYE_EXPOSURE, 511);
		CLEyeSetCameraParameter(_cam, CLEYE_ZOOM, 100);
		CLEyeSetCameraParameter(_cam, CLEYE_ROTATION, 0);

		// Start capturing
		CLEyeCameraStart(_cam);
		cvGetImageRawData(pCapImage, &pCapBuffer);

		IplImage *pDestinationImage;
		//if(_mode == CLEYE_COLOR_PROCESSED || _mode == CLEYE_COLOR_RAW)
			pDestinationImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);
		//else
			//pDestinationImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);

		CvMat *map_matrix;
		CvPoint2D32f src_pnt[4], dst_pnt[4];
		src_pnt[0] = cvPoint2D32f (25*2, 12*2);
		src_pnt[1] = cvPoint2D32f (4*2, 120*2);
		src_pnt[2] = cvPoint2D32f (154*2, 120*2);
		src_pnt[3] = cvPoint2D32f (136*2, 14*2);

		dst_pnt[0] = cvPoint2D32f (19*2, 12*2);
		dst_pnt[1] = cvPoint2D32f (19*2, 120*2);
		dst_pnt[2] = cvPoint2D32f (141*2, 120*2);
		dst_pnt[3] = cvPoint2D32f (141*2, 12*2);

		// image capturing loop
		while(_running)
		{
			CLEyeCameraGetFrame(_cam, pCapBuffer);

			map_matrix = cvCreateMat (3, 3, CV_32FC1);
			cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

			cvWarpPerspective (pCapImage, pDestinationImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));

			cvShowImage(_windowName, pDestinationImage);
		}
		// Stop camera capture
		CLEyeCameraStop(_cam);
		// Destroy camera object
		CLEyeDestroyCamera(_cam);
		// Destroy the allocated OpenCV image
		cvReleaseImage(&pCapImage);
		_cam = NULL;
	}
	static DWORD WINAPI CaptureThread(LPVOID instance)
	{
		// seed the rng with current tick count and thread id
		srand(GetTickCount() + GetCurrentThreadId());
		// forward thread to Capture function
		CLEyeCameraCapture *pThis = (CLEyeCameraCapture *)instance;
		pThis->Run();
		return 0;
	}
};

// Main program entry point
int cameraMain()
{
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
	return 0;
}
