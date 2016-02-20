#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy offenseDefenseStrategy;
	Strategy::DefenseStrategy defenseStrategy;
	Strategy::OffenseStrategy offenseStrategy;
	Strategy::PerfectDefenseStrategy perfectDefenseStrategy;
	//cvNamedWindow("strategy", CV_WINDOW_AUTOSIZE);
	/*IplImage* offenseImage = cvLoadImage("../image/offense.png");
	IplImage* offenseDefenseImage = cvLoadImage("../image/offenseDefense.png");
	IplImage* defenseImage = cvLoadImage("../image/defense.png");*/
				
	//int randamNumber = 0;
	while(1){
		//0-9のランダムな数字を生成。
		int randamNumber = rand() % 10;
		//2(Offense):2(OffenseDefense):6(Defense)の割合
		
		if(randamNumber < 1){
			//cvShowImage("strategy", offenseImage);
			//cvWaitKey(1);
			offenseStrategy.execute();
		}
		else if(randamNumber < 3){
			//cvShowImage("strategy", offenseDefenseImage);
			//cvWaitKey(1);
			offenseDefenseStrategy.execute();
		}
		else{
			//cvShowImage("strategy", defenseImage);
			//cvWaitKey(1);
			defenseStrategy.execute();
		}
		
		/*if(randamNumber == 0){
			defenseStrategy.execute();
		}
		else if(randamNumber == 1){
			defenseStrategy.execute();
		}
		else if(randamNumber == 2){
			defenseStrategy.execute();
		}
		else if(randamNumber == 3){
			offenseDefenseStrategy.execute();
		}
		else if(randamNumber == 4){
			randamNumber == 0;
		}
		randamNumber++;*/

		//===========単体テスト===========
		//offenseStrategy.execute();
		//offenseDefenseStrategy.execute();
		//defenseStrategy.execute();
		//perfectDefenseStrategy.execute();
		//===========単体テスト END===========
	}
}
}  // namespace UI
