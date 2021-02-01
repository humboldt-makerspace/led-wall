#include "utils/Bars.hpp"
#include "system/Interface.hpp"

void Bars::showBar (int x, int y)
{
	for (int i = 0; i < WALL_HEIGHT; i++) {
		if (i <= y) Interface::ledOn(x, i, ColorGradient::colors[x][i]);
		else Interface::fadeToColor(x, i, CRGB::Black, FADE_FACTOR_BARS);
	}	
}
