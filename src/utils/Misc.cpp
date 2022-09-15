#include "utils/Misc.hpp"
#include "system/Interface.hpp"

float Misc::logBaseX(float base, float value)
{
	return (log10(value) / log10(base));
}

bool Misc::outOfBounds(int x, int y)
{
	return (x < 0 || x > WALL_WIDTH - 1 || y < 0 || y > WALL_HEIGHT - 1);
}

int Misc::charToInt(char c)
{
	int t = (int)c;
	if (t > 47 && t < 58) return t - 48;
	else return -1;
}

String Misc::numToWord(int num)
{
	switch (num) {
		case 0: return "null";
		case 1: return "eins";
		case 2: return "zwei";
		case 3: return "drei";
		case 4: return "vier";
		case 5: return "fuenf";
		case 6: return "sechs";
		case 7: return "sieben";
		case 8: return "acht";
		case 9: return "neun";
		default: return "wosdes";
	}
}
