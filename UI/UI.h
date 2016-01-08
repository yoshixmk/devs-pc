#ifndef UI_UI_H
#define UI_UI_H

#include "../ShowWindow/WindowManagement.h"
#include "Mode.h"
#include <iostream>

namespace UI {
class UI {
private:
	//Mode mode;
	ShowWindows::WindowManagement windowManagement;

public:
	void main();

};

}  // namespace UI
#endif
