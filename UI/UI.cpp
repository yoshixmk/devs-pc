#include "UI.h"

namespace UI {

void UI::main() {
	Strategy::OffenseDefenseStrategy mOffenseDefenseStrategy;
	mOffenseDefenseStrategy.execute();
}
}  // namespace UI
