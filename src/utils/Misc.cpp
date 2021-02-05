#include "utils/Misc.hpp"
#include "system/Interface.hpp"

double Misc::logBaseX (double base, double value)
{
	return (log10(value) / log10(base));
}

bool Misc::outOfBounds (int x, int y)
{
	return (x < 0 || x > WALL_WIDTH - 1 || y < 0 || y > WALL_HEIGHT - 1);
}

int Misc::charToInt (char c)
{
	int t = (int) c;
	if (t > 47 && t < 58) return t - 48;
	else return -1;
}
