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

#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "../CLEye/CLEyeMulticam.h"
#include "../CLEye/opencv.hpp"

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
		int cameraMain();
		double GetRandomNormalized();
};

#endif
