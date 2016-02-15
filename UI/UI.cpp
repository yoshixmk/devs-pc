#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy offenseDefenseStrategy;
	Strategy::DefenseStrategy defenseStrategy;
	Strategy::OffenseStrategy offenseStrategy;
	int randamNumber = 0;
	while(1){
		//0-9のランダムな数字を生成。
		//int randamNumber = rand() % 5;
		//3(OffenseDefense):7(Defense)の割合
		randamNumber = 1;
		if(randamNumber%5 == 0){
			offenseDefenseStrategy.execute();
		}
		else{
			//defenseStrategy.execute();
			offenseStrategy.execute();
		}
		randamNumber++;
	}
}
}  // namespace UI
