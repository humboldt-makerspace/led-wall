#ifndef FIGURES_HPP
#define FIGURES_HPP

#include "system/Interface.hpp"

class Figures {
private:
	/* variables */
	static boolean alphabet[NUM_FIGURES][FIGURE_WIDTH][FIGURE_HEIGHT];

public:
	/* functions */
	static void defineAlphabet (void);
	static void displayFigure (Figure figure, int x, int y);
	static void displayColon (int x, int y);
};

#endif
