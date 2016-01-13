#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

#include "../Hardware/Camera.h"
#include "PerspectiveTransformation.h"
#include "../CLEye/opencv.hpp"
#include <iostream>

namespace Color
{
class TwoImageSynthesis
{
private:
	Color::PerspectiveTransformation perspectiveTransformation;
	cv::Mat mMatSynthesisImage;
	cv::Mat mMatNonDistortionImage;

protected:
	Hardware::Camera mCamera;

public:
	TwoImageSynthesis();
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();

};

}  // namespace Color
#endif
