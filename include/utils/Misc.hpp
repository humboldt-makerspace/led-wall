#ifndef MISC_HPP
#define MISC_HPP

#include "Arduino.h"

class Misc {
private:

public:
	/* functions */
	static float logBaseX(float base, float value);
	static bool outOfBounds(int x, int y);
	static int charToInt(char c);
	static String numToWord(int num);
};

#endif
