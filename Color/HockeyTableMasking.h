#ifndef COLOR_HOCKEY_TABLE_MASKING_H
#define COLOR_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include "../CLEye/opencv.hpp"

namespace Color
{
class HockeyTableMasking : public Masking
{
private:
	IplImage* mHockeyTableImage;
	TwoImageSynthesis mTwoImageSynthesis;

public:
	HockeyTableMasking();
//	~HockeyTableMasking();
	IplImage* mask();
};

}  // namespace Color
#endif
