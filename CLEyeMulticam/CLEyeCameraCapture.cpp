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

#include "CLEyeCameraCapture.h"

CLEyeCameraCapture::CLEyeCameraCapture(GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps) :
	_cameraGUID(cameraGUID), _cam(NULL), _mode(mode), _resolution(resolution), _fps(fps), _running(false)
{
	//strcpy(_windowName, windowName);
}
bool CLEyeCameraCapture::StartCapture()
{
	_running = true;
	//cvNamedWindow(_windowName, CV_WINDOW_AUTOSIZE);
	// Start CLEye image capture thread
	/*_hThread = CreateThread(NULL, 0, &CLEyeCameraCapture::CaptureThread, this, 0, 0);
	if(_hThread == NULL)
	{
		MessageBox(NULL,"Could not create capture thread","CLEyeMulticamTest", MB_ICONEXCLAMATION);
		return false;
	}*/
	return true;
}
void CLEyeCameraCapture::StopCapture()
{
	if(!_running)	return;
	_running = false;
}
void CLEyeCameraCapture::IncrementCameraParameter(int param)
{
	if(!_cam)	return;
	printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
	CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param)+10);
}
void CLEyeCameraCapture::DecrementCameraParameter(int param)
{
	if(!_cam)	return;
	printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
	CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param)-10);
}

void CLEyeCameraCapture::run()
{
	/*CvMat *map_matrix;
	CvPoint2D32f src_pnt[4], dst_pnt[4];
	src_pnt[0] = cvPoint2D32f (25*2, 12*2);
	src_pnt[1] = cvPoint2D32f (4*2, 120*2);
	src_pnt[2] = cvPoint2D32f (154*2, 120*2);
	src_pnt[3] = cvPoint2D32f (136*2, 14*2);

	dst_pnt[0] = cvPoint2D32f (19*2, 12*2);
	dst_pnt[1] = cvPoint2D32f (19*2, 120*2);
	dst_pnt[2] = cvPoint2D32f (141*2, 120*2);
	dst_pnt[3] = cvPoint2D32f (141*2, 12*2);*/

	CLEyeCameraGetFrame(_cam, pCapBuffer);

	/*map_matrix = cvCreateMat (3, 3, CV_32FC1);
	cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

	cvWarpPerspective (pCapImage, mCameraImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));*/
}

IplImage* CLEyeCameraCapture::getCameraImage(){
	return mCameraImage;
}

void CLEyeCameraCapture::initCamera()
{
	// Create camera instance
	_mode = CLEYE_COLOR_PROCESSED;
	_fps = 60;
	_resolution = CLEYE_QVGA;
	_cam = CLEyeCreateCamera(_cameraGUID, _mode, _resolution, _fps);
	if(_cam == NULL)		return;
	// Get camera frame dimensions
	CLEyeCameraGetFrameDimensions(_cam, w, h);
	//pCapImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);
	mCameraImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 4);

	// Set some camera parameters
	CLEyeSetCameraParameter(_cam, CLEYE_GAIN, 0);
	CLEyeSetCameraParameter(_cam, CLEYE_EXPOSURE, 90);
	CLEyeSetCameraParameter(_cam, CLEYE_ZOOM, 0);
	CLEyeSetCameraParameter(_cam, CLEYE_ROTATION, 0);

	// Start capturing
	CLEyeCameraStart(_cam);
	//(pCapImage, &pCapBuffer);
	cvGetImageRawData(mCameraImage, &pCapBuffer);
}

void CLEyeCameraCapture::finalCamera()
{
	// Stop camera capture
	CLEyeCameraStop(_cam);
	// Destroy camera object
	CLEyeDestroyCamera(_cam);
	// Destroy the allocated OpenCV image
	//cvReleaseImage(&pCapImage);
	_cam = NULL;
}

void CLEyeCameraCapture::setPerspectiveTransform(int horizontalValue, int verticalValue)
{
	CLEyeSetCameraParameter(_cam, CLEYE_HKEYSTONE, horizontalValue);
	CLEyeSetCameraParameter(_cam, CLEYE_VKEYSTONE, verticalValue);
}

void CLEyeCameraCapture::setHorizontalFlip(bool value)
{
	CLEyeSetCameraParameter(_cam, CLEYE_HFLIP, value);
}

void CLEyeCameraCapture::setVerticalFlip(bool value)
{
	CLEyeSetCameraParameter(_cam, CLEYE_VFLIP, value);
}
