#include "OffenseDefenseStrategy.h"

namespace Strategy {

//void OffenseDefenseStrategy::initialize() {
//}

void OffenseDefenseStrategy::execute()
{
	CvPoint packNowCorrdinate = mPackCoordinate.getCoordinate();
	CvPoint packPreCorrdinate = mPackCoordinate.getPreviousCoordinate();
	CvPoint malletNowCoordinate = mMalletCoordinate.getCoordinate();

}

//void OffenseDefenseStrategy::terminate() {
//}
}  // namespace Strategy
