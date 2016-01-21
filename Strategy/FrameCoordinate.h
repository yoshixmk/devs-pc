#ifndef STRATEGY_FRAME_COORDINATE_H
#define STRATEGY_FRAME_COORDINATE_H

#include "../Strategy/Coordinate.h"
#include "../CLEye/opencv.hpp"

namespace Strategy {
	class FrameCoordinate : public Coordinate {
	private:
		//座標はすべて枠の内側
		static CvPoint mUpperLeftF;
		static CvPoint mLowerLeftF;
		static CvPoint mUpperRightF;
		static CvPoint mLowerRightF;
		static CvPoint mUpperLeftG;
		static CvPoint mLowerLeftG;
		static CvPoint mUpperRightG;
		static CvPoint mLowerRightG;
		static CvPoint mRobotGoalLeft;
		static CvPoint mRobotGoalRight;
		
		//中央のX座標ラインと、Y座標ライン。
		static CvPoint mCenterLine;

	public:
		static CvPoint getUpperLeftF();
		static CvPoint getLowerLeftF();
		static CvPoint getUpperRightF();
		static CvPoint getLowerRightF();
		static CvPoint getUpperLeftG();
		static CvPoint getLowerLeftG();
		static CvPoint getUpperRightG();
		static CvPoint getLowerRightG();
		static CvPoint getRobotGoalLeft();
		static CvPoint getRobotGoalRight();
		static CvPoint getCenterLine();
	};

}  // namespace Strategy
#endif