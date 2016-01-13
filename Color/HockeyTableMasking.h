﻿#ifndef COLOR_HOCKEY_TABLE_MASKING_H
#define COLOR_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include "../CLEye/opencv.hpp"
#include "NonFlipTwoImageSynthesis.h"

namespace Color
{
class HockeyTableMasking : public Masking
{
private:
	IplImage* mHockeyTableImage;
	//TwoImageSynthesis -> NonFlipTwoImageSynthesis へ変更
	NonFlipTwoImageSynthesis mTwoImageSynthesis;

public:
	HockeyTableMasking();
	IplImage* mask();
};

}  // namespace Color
#endif
