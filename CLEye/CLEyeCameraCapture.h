#ifndef CLEYE_CLEYECAMERACAPTURE_H
#define CLEYE_CLEYECAMERACAPTURE_H

#include "CLEyeMulticam.h"
#include "targetver.h"
#include <opencv2/opencv.hpp>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

namespace CLEye {
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

	private:
		double GetRandomNormalized()
		{
			return (double)(rand() - (RAND_MAX >> 1)) / (double)(RAND_MAX >> 1);
		}
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
			if (_hThread == NULL)
			{
				MessageBox(NULL, "Could not create capture thread", "CLEyeMulticamTest", MB_ICONEXCLAMATION);
				return false;
			}
			return true;
		}
		void StopCapture()
		{
			if (!_running)	return;
			_running = false;
			WaitForSingleObject(_hThread, 1000);
			cvDestroyWindow(_windowName);
		}
		void IncrementCameraParameter(int param)
		{
			if (!_cam)	return;
			printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
			CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param) + 10);
		}
		void DecrementCameraParameter(int param)
		{
			if (!_cam)	return;
			printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
			CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param) - 10);
		}
		void Run()
		{
			int w, h;
			IplImage *pCapImage;
			PBYTE pCapBuffer = NULL;
			// Create camera instance
			_cam = CLEyeCreateCamera(_cameraGUID, _mode, _resolution, _fps);
			if (_cam == NULL)		return;
			// Get camera frame dimensions
			CLEyeCameraGetFrameDimensions(_cam, w, h);
			// Depending on color mode chosen, create the appropriate OpenCV image
			if (_mode == CLEYE_COLOR_PROCESSED || _mode == CLEYE_COLOR_RAW)
				pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);
			else
				pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);

			// Set some camera parameters
			CLEyeSetCameraParameter(_cam, CLEYE_GAIN, 0);
			CLEyeSetCameraParameter(_cam, CLEYE_EXPOSURE, 511);
			CLEyeSetCameraParameter(_cam, CLEYE_ZOOM, (int)(GetRandomNormalized()*100.0));
			CLEyeSetCameraParameter(_cam, CLEYE_ROTATION, (int)(GetRandomNormalized()*300.0));

			// Start capturing
			CLEyeCameraStart(_cam);
			cvGetRawData(pCapImage, &pCapBuffer);
			// image capturing loop
			while (_running)
			{
				CLEyeCameraGetFrame(_cam, pCapBuffer);

				cvShowImage(_windowName, pCapImage);
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

}  // namespace CLEye
#endif