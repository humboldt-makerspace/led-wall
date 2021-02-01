#ifndef MOVING_HPP
#define MOVING_HPP

#include "constants.hpp"
#include "Geom.h"

class Moving {
private:

public:
	/* variables */
	static Dot matrixDots[MAX_NUM_DOTS_MATRIX];
	static Dot processorDots[MAX_NUM_DOTS_PROCESSOR];

	/* functions */
	static void initDots (void);
	static void createDot (int x, int y);
	static void createDot (int x, int y, Side origin);
	static void autoResetDots (void);
	static void moveDot (int index, Direction dir);
	static void updateBuffer (int index, Point p);
	static void showDot (int i);
};

#endif
