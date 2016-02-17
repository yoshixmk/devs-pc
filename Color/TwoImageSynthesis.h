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
	IplImage* mImgRobotSide;
	IplImage* mImgHumanSide;
	Color::PerspectiveTransformation perspectiveTransformation;

protected:
	IplImage* mSynthesisImage;
	cv::Mat mMatSynthesisImage;
	cv::Mat mMatNonDistortionImage;

public:
	TwoImageSynthesis();
	~TwoImageSynthesis();
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();

};

}  // namespace Color
#endif
