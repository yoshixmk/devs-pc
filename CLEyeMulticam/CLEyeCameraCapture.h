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
#ifndef CLEYEMULTICAM_CLEYEMULTICAPTURE_H
#define CLEYEMULTICAM_CLEYEMULTICAPTURE_H

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
		GUID _cameraGUID;
		CLEyeCameraInstance _cam;
		CLEyeCameraColorMode _mode;
		CLEyeCameraResolution _resolution;
		float _fps;
		HANDLE _hThread;
		bool _running;
		IplImage* mCameraImage; //変形した画像
		IplImage *pCapImage; //original
		PBYTE pCapBuffer; //originalを作るためのバッファ
		int w, h;

	public:
		CLEyeCameraCapture(GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps);
		bool StartCapture();
		void StopCapture();
		void IncrementCameraParameter(int param);//デバッグ用
		void DecrementCameraParameter(int param);//デバッグ用
		
		IplImage* getCameraImage();
		void initCamera();
		void finalCamera();
		void run(); //->Runからrunに変更
	
		void setPerspectiveTransform(int horizontalValue, int verticalValue);
		void setHorizontalFlip(bool value);
		void setVerticalFlip(bool value);
};

#endif
