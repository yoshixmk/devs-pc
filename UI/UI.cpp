#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy offenseDefenseStrategy;
	Strategy::DefenseStrategy defenseStrategy;
	//int randamNumber = 0;
	while(1){
		//0-9のランダムな数字を生成。
		int randamNumber = rand() % 3;

		//3(OffenseDefense):7(Defense)の割合
		if(randamNumber < 3){
			offenseDefenseStrategy.execute();
		}
		else{
			defenseStrategy.execute();
		}
	}
}
}  // namespace UI
