#ifndef COLOR_GRADIENT_HPP
#define COLOR_GRADIENT_HPP

#include "system/Interface.hpp"

class ColorGradient {
private:
	/* variables */
	static CRGB colorsHorizontal[WALL_WIDTH];
	static CRGB colorsVertical[WALL_HEIGHT];

	/* functions */
	static void fillCompleteWall(ColorMode mode);

public:
	/* variables */
	static CRGB colors[WALL_WIDTH][WALL_HEIGHT];

	/* functions */
	static void changeColorGradient(ColorMode mode);
};

#endif
