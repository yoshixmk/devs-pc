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
#ifndef CLEYEMULTICAM_CLEYEMULTICAM_DETECTION_H
#define CLEYEMULTICAM_CLEYEMULTICAM_DETECTION_H

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#include "../CLEye/CLEyeMulticam.h"
#include "../CLEye/opencv.hpp"
//#include "CLEyeMulticam.h"
//#include "opencv.hpp"

static LARGE_INTEGER _frequencyPT;

static inline PVOID ProfileMSStart()
{
	PLARGE_INTEGER start = new LARGE_INTEGER;
	QueryPerformanceFrequency(&_frequencyPT);
	QueryPerformanceCounter(start);
	return (PVOID)start;
}

static inline double ProfileMSEnd(PVOID p)
{
	LARGE_INTEGER stop, diff;
	PLARGE_INTEGER start = (PLARGE_INTEGER)p;
	QueryPerformanceCounter(&stop);
	diff.QuadPart = stop.QuadPart - start->QuadPart;
	double timeMs = 1000.0 * ((double)diff.QuadPart / (double)_frequencyPT.QuadPart);
	delete start;
	return timeMs;
}

// Sample camera capture class
class CLEyeCameraCapture
{
	private:
		CHAR _windowName[256];
		GUID _cameraGUID;
		CLEyeCameraInstance _cam;
		CLEyeCameraColorMode _mode;
		CLEyeCameraResolution _resolution;
		float _fps;
		HANDLE _hThread;
		bool _running;

	public:
		CLEyeCameraCapture(LPSTR windowName, GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps);
		bool StartCapture();
		void StopCapture();
		void IncrementCameraParameter(int param);
		void DecrementCameraParameter(int param);
		void Run();
		static DWORD WINAPI CaptureThread(LPVOID instance);
		double GetRandomNormalized();
};

#endif

