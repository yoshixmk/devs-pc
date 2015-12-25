#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching(char aXaxisOrYaxis)
{
	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 0;
	mNowDirection = 'R';
	mTargetTime = 0;
	
}

FrequencySwitching::~FrequencySwitching()
{

}

void FrequencySwitching::output()
{
	/*if(mXaxisOrYaxis == 'X'){
		double now_time = mTimer.getOperatingTime();
		int i;
		int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);

		//加速
		if(now_time < mTargetTime){
			//減速のときのために周波数のインデックスを更新
			if(now_time < 0.05 * (array_num)){ //本番0.05s
				for(i=0; i<array_num; i++){
					if(mFrequency[i] == mCurrentFrequency){
						mFrequencyIndex = i;
					}
				}
			}
			for(i=0; i<array_num; i++){
				if(now_time < 0.05 * (i+1)){ //本番0.05s
					if(mCurrentFrequency != mFrequency[i]){
						mCurrentFrequency = mFrequency[i];
						mMotorDriverX->setPulse(mCurrentFrequency);

						if(mTargetDirection == 'R'){
							mMotorDriverX->setCwCcw(1);
						}
						if(mTargetDirection == 'L'){
							mMotorDriverX->setCwCcw(0);
						}
					}
					break;
				}
			}
			mMotorDriverX->output();
			mMovingStopTimer.resetStartOperatingTime();//停止動作に移った場合のため
		}
		else{ //減速
			double now_stop_time = mMovingStopTimer.getOperatingTime();
			for(i=0; i<=mFrequencyIndex; i++){
				if(now_stop_time <= 0.05 * i){ //本番0.05s
					if(mCurrentFrequency != mFrequency[mFrequencyIndex - i]){
						mCurrentFrequency = mFrequency[mFrequencyIndex - i];
						mMotorDriverX->setPulse(mCurrentFrequency);

						if(mTargetDirection == 'R'){
							mMotorDriverX->setCwCcw(1);
						}
						if(mTargetDirection == 'L'){
							mMotorDriverX->setCwCcw(0);
						}
						mMotorDriverX->output();
					}
					break;
				}
				else if(0.05 * (array_num - 1) < now_stop_time){//本番0.05s
					mCurrentFrequency = 0;
					mMotorDriverX->stopOutput();
				}
			}
	//		std::cout << mCurrentFrequency << std::endl;
		}
	}
	else if(mXaxisOrYaxis == 'Y'){
		double now_time = mTimer.getOperatingTime();
		int i;
		int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);

		//加速
		if(now_time < mTargetTime){
			//減速のときのために周波数のインデックスを更新
			if(now_time < 0.05 * (array_num)){ //本番0.05s
				for(i=0; i<array_num; i++){
					if(mFrequency[i] == mCurrentFrequency){
						mFrequencyIndex = i;
					}
				}
			}
			for(i=0; i<array_num; i++){
				if(now_time < 0.05 * (i+1)){ //本番0.05s
					if(mCurrentFrequency != mFrequency[i]){
						mCurrentFrequency = mFrequency[i];
						mMotorDriverY1->setPulse(mCurrentFrequency);
						mMotorDriverY2->setPulse(mCurrentFrequency);

						if(mTargetDirection == 'U'){
							mMotorDriverY1->setCwCcw(1);
							mMotorDriverY2->setCwCcw(0);
						}
						if(mTargetDirection == 'D'){
							mMotorDriverY1->setCwCcw(0);
							mMotorDriverY2->setCwCcw(1);
						}
					}
					break;
				}
			}
			mMotorDriverY1->output();
			mMotorDriverY2->output();
			mMovingStopTimer.resetStartOperatingTime();//停止動作に移った場合のため
		}
		else{ //減速
			double now_stop_time = mMovingStopTimer.getOperatingTime();
			for(i=0; i<=mFrequencyIndex; i++){
				if(now_stop_time <= 0.05 * i){ //本番0.05s
					if(mCurrentFrequency != mFrequency[mFrequencyIndex - i]){
						mCurrentFrequency = mFrequency[mFrequencyIndex - i];
						mMotorDriverY1->setPulse(mCurrentFrequency);
						mMotorDriverY2->setPulse(mCurrentFrequency);

						if(mTargetDirection == 'U'){
							mMotorDriverY1->setCwCcw(1);
							mMotorDriverY2->setCwCcw(0);
						}
						if(mTargetDirection == 'D'){
							mMotorDriverY1->setCwCcw(0);
							mMotorDriverY2->setCwCcw(1);
						}
						mMotorDriverY1->output();
						mMotorDriverY2->output();
					}
					break;
				}
				else if(0.05 * (array_num - 1) < now_stop_time){//本番0.05s
					mCurrentFrequency = 0;
					mMotorDriverY1->stopOutput();
					mMotorDriverY2->stopOutput();
				}
			}
	//		std::cout << mCurrentFrequency << std::endl;
		}
	}*/
}

void FrequencySwitching::stop()
{
	
}

}  // namespace Strategy
