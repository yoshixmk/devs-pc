#include "Locus.h"

namespace Strategy
{
Locus::Locus()
{
	mAInclination = 0;
	mBIntercept = 0;
	mIsRandom = false;
}

CvPoint Locus::getLocusCoordinate(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine)
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
				break;
			}
		}
	}
	else{
		mAInclination = 0;
		mBIntercept = 0;
		//当たり障りのない位置（中央）を指定
		int centerLine = FrameCoordinate::getLowerRightF().x + FrameCoordinate::getLowerLeftF().x;
		targetCoordinate = cvPoint(centerLine, aYLine);
	}

	return targetCoordinate;
}

void Locus::calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2)
{
	if((aCoordinate2.x - aCoordinate1.x) != 0){
		mAInclination = (aCoordinate2.y - aCoordinate1.y) / (aCoordinate2.x - aCoordinate1.x);
		mBIntercept = aCoordinate2.y - mAInclination * aCoordinate2.x;
	}
	else{
		mAInclination = 0;
		mBIntercept = 0;
	}
}

double Locus::getAInclination()
{
	return mAInclination;
}

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

//基本的には、getFrameOutPoint()の後に利用すればいい。
void Locus::setNextAB()
{
	int a = getAInclination();
	int b = getBIntercept();
	int frameWidth = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x) / 2 - (FrameCoordinate::getLowerLeftF().x + FrameCoordinate::getUpperLeftF().x) / 2;
	int frameX = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x) / 2;
	int h = frameWidth * a;

	if(a < 0){
		h *= -1;
	}
	
	if(a > 0){
		int y = a * frameX + b;
		mBIntercept += h;//(y - a * frameX) * 2;
		std::cout << "a: " << a;
		std::cout << "  b: " << b << std::endl;
	}
	mAInclination *= -1;
}

/*void Locus::oldLocus(IplImage* show_img)
{
	int a_inclination = mAInclination;
	int b_intercept = mBIntercept;
	
	

	int left_frame = FrameCoordinate::getLowerLeftF().x;
	int right_frame = FrameCoordinate::getUpperRightF().x;
	int origin_coordinateY = a_inclination * left_frame + b_intercept;
	int gX_after = mCoordinate1.x;
	int gY_after = mCoordinate1.y;
	int center_line = FrameCoordinate::getLowerRightF().x  - FrameCoordinate::getLowerLeftF().x;
	int target_coordinateY = 350;
	int target_coordinateX = (target_coordinateY - mBIntercept) - mAInclination;
	int target_destanceY = 350 - gY_after;
		//一次関数で目標X座標の計算
	if(a_inclination){
		target_coordinateX = (int)((target_destanceY - b_intercept) / a_inclination);
	}
	if(target_coordinateX < left_frame){
		cvLine(show_img, cvPoint((int)gX_after, (int)gY_after), cvPoint(left_frame, origin_coordinateY), cvScalar(0,255,255), 2);
	}
	else if(FrameCoordinate::getUpperRightF().x < target_coordinateX){
		cvLine(show_img, cvPoint((int)gX_after, (int)gY_after), cvPoint(right_frame, origin_coordinateY), cvScalar(0,255,255), 2);
	}
	else{
		cvLine(show_img, cvPoint((int)gX_after, (int)gY_after), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
	}

	int rebound_max = 5;
	int rebound_num = 0;

	while(target_coordinateX < left_frame || right_frame < target_coordinateX){
		if(target_coordinateX < left_frame){ //左側の枠での跳ね返り後の軌跡。左枠側平均
			target_coordinateX = 2 * left_frame - target_coordinateX;
			b_intercept -= 2 * ((-a_inclination) * left_frame);
			a_inclination = -a_inclination;
			origin_coordinateY = a_inclination * left_frame + b_intercept;
			if(target_coordinateX < right_frame){
				cvLine(show_img, cvPoint(left_frame, origin_coordinateY), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
			}
			else{
				//左側の枠から右側の枠に当たるときのY座標
				target_coordinateY = a_inclination * right_frame + b_intercept;
				cvLine(show_img, cvPoint(left_frame, origin_coordinateY), cvPoint(right_frame, target_coordinateY), cvScalar(0,255,255), 2);
			}
		}
		else if(right_frame < target_coordinateX){ //右側の枠での跳ね返り後の軌跡。右枠側平均
			target_coordinateX = 2 * right_frame - target_coordinateX;
			b_intercept += 2 * (a_inclination * right_frame);
			a_inclination= -a_inclination;
			//cvLine(show_img, cvPoint(right_frame, b_intercept), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,0,255), 2);
			origin_coordinateY = a_inclination * right_frame + b_intercept;
			if(left_frame < target_coordinateX){
				cvLine(show_img, cvPoint(right_frame, origin_coordinateY), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
			}
			else{
				//右側の枠から左側の枠に当たるときのY座標
				target_coordinateY = a_inclination * left_frame + b_intercept;
				cvLine(show_img, cvPoint(right_frame, origin_coordinateY), cvPoint(left_frame, target_coordinateY), cvScalar(0,255,255), 2);
			}
		}
		rebound_num++;
		if(rebound_max < rebound_num){
			//跳ね返りが多すぎる時は、中央を指定
			target_coordinateX = center_line;
			break;
		}
	}
}*/

}  // namespace Strategy
