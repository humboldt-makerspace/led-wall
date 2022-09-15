#ifndef FIGURES_HPP
#define FIGURES_HPP

#include "system/Interface.hpp"

class Figures {
private:
	/* variables */
	static boolean alphabet[NUM_FIGURES][FIGURE_WIDTH][FIGURE_HEIGHT];
	static boolean numbers[NUM_BIG_NUM][BIG_NUM_WIDTH][BIG_NUM_HEIGHT];

public:
	/* functions */
	static void defineNumbers(void);
	static void defineAlphabet(void);
	static void displayNumber(BigNumber number, int x, int y);
	static void displayFigure(Figure figure, int x, int y);
	static void displayFigure(Figure figure, int x, int y, CRGB color);
	static void displayFigureHard(Figure figure, int x, int y, CRGB color);
	static void displayColon(int x, int y);
	static Figure charToFigure(char c);
};

#endif
