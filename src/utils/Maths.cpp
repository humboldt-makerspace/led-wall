#include "utils/Maths.hpp"
#include "system/Interface.hpp"

double Maths::logBaseX (double base, double value)
{
	return (log10(value) / log10(base));
}

bool Maths::outOfBounds (int x, int y)
{
	return (x < 0 || x > WALL_WIDTH - 1 || y < 0 || y > WALL_HEIGHT - 1);
}
