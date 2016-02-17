#ifndef COLOR_PERSPECTIVETRANSFORMATION_H_
#define COLOR_PERSPECTIVETRANSFORMATION_H_

#include "../CLEye/opencv.hpp"
#include "../Hardware/Camera.h"

namespace Color
{

class PerspectiveTransformation
{

private:
	Hardware::Camera mCamera;
	IplImage* mRobotSideImage;
	IplImage* mHumanSideImage;

public:
	PerspectiveTransformation();
	~PerspectiveTransformation();
	IplImage* transformRobotSideImage();
	IplImage* transformHumanSideImage();
};

} /* namespace Color */

#endif /* COLOR_PERSPECTIVETRANSFORMATION_H_ */
