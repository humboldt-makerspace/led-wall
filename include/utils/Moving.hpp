#ifndef MOVING_HPP
#define MOVING_HPP

#include "CustomTypes.h"
#include "constants.h"
#include "FastLED.h"

class Moving {
private:

public:
	/* variables */
	static dot_t dots[MAX_NUM_DOTS];
	static int activeDots;
	static int maxNumDots;

	/* functions */
	static void resetDots(void);
	static void createDot(int x, int y, direction_t dir);
	static void removeDot(dot_t &dot);
	static void autoResetDot(dot_t &dot);
	static void moveDot(dot_t &dot);
	static void updateBuffer(dot_t &dot);
	static void showDot(dot_t &dot);
	static void showDot(dot_t &dot, CRGB const &color);
};

#endif
