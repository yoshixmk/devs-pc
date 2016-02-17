#ifndef NON_FLIP_COLOR_TWO_IMAGE_SYNTHESIS_H
#define NON_FLIP_COLOR_TWO_IMAGE_SYNTHESIS_H

#include "TwoImageSynthesis.h"

namespace Color
{
class NonFlipTwoImageSynthesis : public TwoImageSynthesis
{
public:
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();
};

}  // namespace Color
#endif
