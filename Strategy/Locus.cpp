#include "Locus.h"

namespace Strategy
{
Locus::Locus()
{
	mAInclination = 0;
	mBIntercept = 0;
	mIsRandom = false;
}

//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) を使った後、get
CvPoint Locus::getLocusCoordinate()
{
	return mForecastPoint;
}

bool Locus::calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine)
{
	CvPoint targetCoordinate;
	targetCoordinate.y = aYLine;
	int left_frame = FrameCoordinate::getLowerLeftF().x + FrameCoordinate::getUpperLeftF().x ;
	int right_frame = FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x;
	if((aCoordinate2.x - aCoordinate1.x) != 0){
		mAInclination = (aCoordinate2.y - aCoordinate1.y) / (aCoordinate2.x - aCoordinate1.x);
		mBIntercept = aCoordinate2.y - mAInclination * aCoordinate2.x;
		targetCoordinate.x = (int)((aYLine - mBIntercept) / mAInclination);
		
		
		int rebound_max = 3; //3回以上跳ね返る軌跡の場合、当たり障りのない位置（中央）を指定
		int rebound_num = 0;
		while(targetCoordinate.x < left_frame || right_frame < targetCoordinate.x){
			if(targetCoordinate.x < left_frame){
				targetCoordinate.x = 2 * left_frame - targetCoordinate.x;
				mBIntercept -= 2 * ((-mAInclination) * left_frame);
				mAInclination = -mAInclination;
			}
			else if(right_frame < targetCoordinate.x){
				targetCoordinate.x = 2 * right_frame - targetCoordinate.x;
				mBIntercept += 2 * (mAInclination * right_frame);
				mAInclination = -mAInclination;
			}
			rebound_num++;
			if(rebound_max < rebound_num){
				//跳ね返りが多すぎる時は、中央を指定
				targetCoordinate.x = (left_frame + right_frame) / 2;
				//break;
				return false;
			}
		}
	}
	else{
		mAInclination = 0;
		mBIntercept = 0;
		//当たり障りのない位置（中央）を指定
		int centerLine = FrameCoordinate::getLowerRightF().x + FrameCoordinate::getLowerLeftF().x;
		targetCoordinate = cvPoint(centerLine, aYLine);
		return false;
	}
	mForecastPoint = targetCoordinate;

	return true;
}

//
//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) を使った後、get
double Locus::getAInclination()
{
	return mAInclination;
}

//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) を使った後、get
double Locus::getBIntercept()
{
	return mBIntercept;
}

CvPoint Locus::getFrameOutPoint(int aLineY)
{
	int x, y, frameX;
	int a = getAInclination();
	int b = getBIntercept();
	CvPoint coordinate;

	y = aLineY;
	if(a == 0){
		return cvPoint(0,0);
	}
	else{
		x = (y - b) / a;
	}

	if(a < 0)
	{
		frameX = (FrameCoordinate::getLowerLeftF().x + FrameCoordinate::getUpperLeftF().x) / 2;
		if(x < frameX){
			//左壁でぶつかる場所
			coordinate = cvPoint(frameX, a*frameX+b);
		}
		else{
			coordinate = cvPoint(x, y);
		}
	}
	else{
		frameX = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x) / 2;
		if(frameX < x){
			//右壁でぶつかる場所
			coordinate = cvPoint(frameX, a*frameX+b);
		}
		else{
			coordinate = cvPoint(x, y);
		}
	}
	return coordinate;
}

void Locus::setRandom(bool aIsRandoem)
{
	mIsRandom = aIsRandoem;
}

}  // namespace Strategy
