#include "FrameCoordinate.h"

namespace Strategy
{
	CvPoint FrameCoordinate::mUpperLeftF = cvPoint(31, 66);
	CvPoint FrameCoordinate::mLowerLeftF = cvPoint(33, 398);
	CvPoint FrameCoordinate::mUpperRightF = cvPoint(297, 73);
	CvPoint FrameCoordinate::mLowerRightF = cvPoint(290, 410);
	CvPoint FrameCoordinate::mUpperLeftG = cvPoint(76, 28);
	CvPoint FrameCoordinate::mLowerLeftG = cvPoint(83, 441);
	CvPoint FrameCoordinate::mUpperRightG = cvPoint(247, 25);
	CvPoint FrameCoordinate::mLowerRightG = cvPoint(233, 448);
	CvPoint FrameCoordinate::mRobotGoalLeft = cvPoint(116, 447);
	CvPoint FrameCoordinate::mRobotGoalRight = cvPoint(202, 450);
	FrameCoordinate::FrameCoordinate()
	{
	}

	CvPoint FrameCoordinate::getUpperLeftF()
	{
		return mUpperLeftF;
	}

	CvPoint FrameCoordinate::getLowerLeftF()
	{
		return mLowerLeftF;
	}

	CvPoint FrameCoordinate::getUpperRightF()
	{
		return mUpperRightF;
	}

	CvPoint FrameCoordinate::getLowerRightF()
	{
		return mLowerRightF;
	}

	CvPoint FrameCoordinate::getUpperLeftG()
	{
		return mUpperLeftG;
	}

	CvPoint FrameCoordinate::getLowerLeftG()
	{
		return mLowerLeftG;
	}

	CvPoint FrameCoordinate::getUpperRightG()
	{
		return mUpperRightG;
	}

	CvPoint FrameCoordinate::getLowerRightG()
	{
		return mLowerRightG;
	}

	CvPoint FrameCoordinate::getRobotGoalLeft()
	{
		return mRobotGoalLeft;
	}

	CvPoint FrameCoordinate::getRobotGoalRight()
	{
		return mRobotGoalRight;
	}
}  // namespace Strategy