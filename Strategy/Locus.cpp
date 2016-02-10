#include "Locus.h"

namespace Strategy
{
Locus::Locus()
{
	mAInclination = 0;
	mBIntercept = 0;
	mIsRandom = false;
}

//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) ���g������Aget
CvPoint Locus::getLocusCoordinate()
{
	return mForecastPoint;
}

bool Locus::calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine)
{
	CvPoint targetCoordinate;
	targetCoordinate.y = aYLine;
	//�}���b�g�̒��S�܂ł̍��W���l��
	int left_frame = (FrameCoordinate::getLowerLeftF().x + FrameCoordinate::getUpperLeftF().x) / 2 + 10; //�␳���� +10

	int right_frame = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x) / 2 - 10; //�␳���� -10

	int centerLine = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getLowerLeftF().x) / 2;
	if(((aCoordinate2.x - aCoordinate1.x) != 0) && ((aCoordinate2.y - aCoordinate1.y) != 0)){
		mAInclination = (double)(aCoordinate2.y - aCoordinate1.y) / (double)(aCoordinate2.x - aCoordinate1.x);
		mBIntercept = aCoordinate2.y - mAInclination * aCoordinate2.x;
		targetCoordinate.x = (int)((aYLine - mBIntercept) / mAInclination);
		
		int rebound_max = 3; //���ȏ㒵�˕Ԃ�O�Ղ̏ꍇ�A��������̂Ȃ��ʒu�i�����j���w��
		int rebound_num = 0;

		while(targetCoordinate.x < left_frame || right_frame < targetCoordinate.x){
			if(targetCoordinate.x < left_frame){
				//targetCoordinate.x = 2 * left_frame - targetCoordinate.x;
				mBIntercept -= 2 * ((-mAInclination) * left_frame);
				//mAInclination = -mAInclination; //�␳�Ȃ�
				mAInclination = -mAInclination + 0.2; //�␳����
				targetCoordinate.x = (int)((aYLine - mBIntercept) / mAInclination);
			}
			else if(right_frame < targetCoordinate.x){
				//targetCoordinate.x = 2 * right_frame - targetCoordinate.x;
				mBIntercept += 2 * (mAInclination * right_frame);
				//mAInclination = -mAInclination; //�␳�Ȃ�
				mAInclination = -mAInclination - 0.2; //�␳����
				targetCoordinate.x = (int)((aYLine - mBIntercept) / mAInclination);
			}
			rebound_num++;
			if(rebound_max < rebound_num){
				//���˕Ԃ肪�������鎞�́A�������w��
				targetCoordinate = cvPoint(centerLine, aYLine);
				mForecastPoint = targetCoordinate;
				//break;
				return false;
			}
		}
	}
	else{
		mAInclination = 0;
		mBIntercept = 0;
		//��������̂Ȃ��ʒu�i�����j���w��
		targetCoordinate = cvPoint(centerLine, aYLine);
		mForecastPoint = targetCoordinate;
		return false;
	}
	mForecastPoint = targetCoordinate;

	return true;
}

//
//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) ���g������Aget
double Locus::getAInclination()
{
	return mAInclination;
}

//calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2, int aYLine) ���g������Aget
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
			//���ǂłԂ���ꏊ
			coordinate = cvPoint(frameX, a*frameX+b);
		}
		else{
			coordinate = cvPoint(x, y);
		}
	}
	else{
		frameX = (FrameCoordinate::getLowerRightF().x + FrameCoordinate::getUpperRightF().x) / 2;
		if(frameX < x){
			//�E�ǂłԂ���ꏊ
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
