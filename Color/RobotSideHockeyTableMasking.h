#ifndef COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H
#define COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include "../CLEye/opencv.hpp"

namespace Color {
class RobotSideHockeyTableMasking: public Masking {
private:
	IplImage* mRobotSideHockeyTableImage;
	TwoImageSynthesis mTwoImageSynthesis;

public:
	RobotSideHockeyTableMasking();
//	~RobotSideHockeyTableMasking();
	IplImage* mask();
};

}  // namespace Color
#endif
