#ifndef COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H
#define COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include "../CLEye/opencv.hpp"
#include "NonFlipTwoImageSynthesis.h"

namespace Color {
class RobotSideHockeyTableMasking: public Masking {
private:
	IplImage* mRobotSideHockeyTableImage;
	//TwoImageSynthesis -> NonFlipTwoImageSynthesis へ変更
	NonFlipTwoImageSynthesis mTwoImageSynthesis;

public:
	RobotSideHockeyTableMasking();
	IplImage* mask();
	IplImage* getMaskingImage();
};

}  // namespace Color
#endif
