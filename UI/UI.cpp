#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy mOffenseDefenseStrategy;
	Strategy::DefenseStrategy defenseStrategy;

	while(1){
		//0-9のランダムな数字を生成。
		int randamNumber = rand() % 3;

		//3(OffenseDefense):7(Defense)の割合
		if(randamNumber < 3){
			mOffenseDefenseStrategy.execute();
		}
		else{
			defenseStrategy.execute();
		}
	}
}
}  // namespace UI
