#ifndef NON_FLIP_COLOR_TWO_IMAGE_SYNTHESIS_H
#define NON_FLIP_COLOR_TWO_IMAGE_SYNTHESIS_H

#include "TwoImageSynthesis.h"
#include "../Hardware/Camera.h"
#include "../CLEye/opencv.hpp"

namespace Color
{
class NonFlipTwoImageSynthesis : public TwoImageSynthesis
{
private:
	cv::Mat mMatSynthesisImage;
	cv::Mat mNonFlipTwoImageSynthesisImage;
	IplImage* mSynthesisImage;

public:
	NonFlipTwoImageSynthesis();
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();
};

}  // namespace Color
#endif
