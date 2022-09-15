#ifndef MOVING_HPP
#define MOVING_HPP

#include "CustomTypes.h"
#include "constants.h"
#include "FastLED.h"

class Moving {
private:

public:
	/* variables */
	static Dot dots[MAX_NUM_DOTS];
	static int activeDots;
	static int maxNumDots;

	/* functions */
	static void resetDots(void);
	static void createDot(int x, int y, Direction dir);
	static void removeDot(Dot *dot);
	static void autoResetDot(Dot *dot);
	static void moveDot(Dot *dot);
	static void updateBuffer(Dot *dot);
	static void showDot(Dot *dot);
	static void showDot(Dot *dot, CRGB color);
};

#endif
