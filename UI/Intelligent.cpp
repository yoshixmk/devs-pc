#include "Intelligent.h"

namespace UI {

Intelligent::Intelligent()
{
	//default = strong
	mStrongOrWeak = true;
}

int Intelligent::getIntelligent()
{
	return 0;
}

bool Intelligent::isStrong()
{
	return mStrongOrWeak;
}

bool Intelligent::isWeak()
{
	return !mStrongOrWeak;
}
}  // namespace UI
