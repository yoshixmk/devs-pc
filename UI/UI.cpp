#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy offenseDefenseStrategy;
	Strategy::DefenseStrategy defenseStrategy;
	Strategy::OffenseStrategy offenseStrategy;
	//int randamNumber = 0;
	while(1){
		//0-9のランダムな数字を生成。
		int randamNumber = rand() % 10;
		//2(Offense):2(OffenseDefense):6(Defense)の割合
		
		/*if(randamNumber < 2){
			offenseStrategy.execute();
		}
		else if(randamNumber < 4){
			offenseDefenseStrategy.execute();
		}
		else{
			defenseStrategy.execute();
		}*/

		//offenseStrategy.execute();
		offenseDefenseStrategy.execute();
		//defenseStrategy.execute();
	}
}
}  // namespace UI
