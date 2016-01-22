#ifndef TEST_COLORTEST_H_
#define TEST_COLORTEST_H_

#include "../Color/TwoImageSynthesis.h"
#include "../Color/HockeyTableMasking.h"
#include "../Color/RobotSideHockeyTableMasking.h"
#include "../Color/PerspectiveTransformation.h"
#include "../Color/ColorExtraction.h"
#include "../Color/NonFlipTwoImageSynthesis.h"

#include "../Hardware/Timer.h"

#include <iostream>

namespace Test {

class ColorTest {
public:
	ColorTest();
	void twoImageSynthesisTest();
	void hockeyTableMaskingTest();
	void robotSideHockeyTableMaskingTest();
	void perspectiveTransformationTest();
	void colorExtractionTest();
	void nonFlipTwoImageSynthesisTest();
};

} /* namespace Test */

#endif /* TEST_COLORTEST_H_ */
