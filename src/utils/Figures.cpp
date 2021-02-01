#include "utils/Figures.hpp"
#include "system/Interface.hpp"

boolean Figures::alphabet[NUM_FIGURES][FIGURE_WIDTH][FIGURE_HEIGHT];

void Figures::defineAlphabet (void)
{
	for (int i = 0; i < NUM_FIGURES; i++) {
		for (int x = 0; x < FIGURE_WIDTH; x++) {
			for (int y = 0; y < FIGURE_HEIGHT; y++) {
				alphabet[i][x][y] = false;
			}
		}
	}

	for (int x = 0; x < FIGURE_WIDTH; x++) {
		for (int y = 0; y < FIGURE_HEIGHT; y++) {
			/* 0 */
			if (y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2 ||
				x == 0 ||
				x == 1 ||
				x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2) alphabet[N0][x][y] = true;

			/* 1 */
			if (x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2) alphabet[N1][x][y] = true;

			/* 2 */
			if (((x == 0 || x == 1) && y < FIGURE_HEIGHT / 2) ||
				((x == FIGURE_WIDTH - 1 || x == FIGURE_WIDTH - 2) && y > FIGURE_HEIGHT / 2) ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N2][x][y] = true;

			/* 3 */
			if (x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N3][x][y] = true;

			/* 4 */
			if (x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2 ||
				((x == 0 || x == 1) && y > FIGURE_HEIGHT / 2) ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1) alphabet[N4][x][y] = true;

			/* 5 */
			if (((x == 0 || x == 1) && y > FIGURE_HEIGHT / 2) ||
				((x == FIGURE_WIDTH - 1 || x == FIGURE_WIDTH - 2) && y < FIGURE_HEIGHT / 2) ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N5][x][y] = true;
			
			/* 6 */
			if (x == 0 ||
				x == 1 ||
				((x == FIGURE_WIDTH - 1 || x == FIGURE_WIDTH - 2) && y < FIGURE_HEIGHT / 2) ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N6][x][y] = true;
			
			/* 7 */
			if (x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N7][x][y] = true;

			/* 8 */
			if (x == 0 ||
				x == 1 ||
				x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2 ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2) alphabet[N8][x][y] = true;

			/* 9 */
			if (x == FIGURE_WIDTH - 1 ||
				x == FIGURE_WIDTH - 2 ||
				y == 0 ||
				y == 1 ||
				y == FIGURE_HEIGHT / 2 ||
				y == FIGURE_HEIGHT / 2 - 1 ||
				y == FIGURE_HEIGHT - 1 ||
				y == FIGURE_HEIGHT - 2 ||
				((x == 0 || x == 1) && y > FIGURE_HEIGHT / 2)) alphabet[N9][x][y] = true;
		}
	}
}

void Figures::displayColon (int x, int y)
{
	
	if (x > WALL_WIDTH - 2 || y > WALL_HEIGHT - 5) return;

	Interface::ledOn(x, y, ColorGradient::colors[x][y]);
	Interface::ledOn(x, y + 3, ColorGradient::colors[x][y + 3]);

}

void Figures::displayFigure (Figure figure, int x, int y)
{
	if (x > WALL_WIDTH - FIGURE_WIDTH ||
		y > WALL_HEIGHT - FIGURE_HEIGHT) return;
	for (int i = 0; i < FIGURE_WIDTH; i++) {
		for (int j = 0; j < FIGURE_HEIGHT; j++) {
			if (!alphabet[figure][i][j]) Interface::fadeToColor(x + i, y + j, CRGB::Black, FADE_FACTOR_CLOCK);
			else Interface::fadeToColor(x + i, y + j, ColorGradient::colors[x + i][y + j], FADE_FACTOR_CLOCK);
		}
	}
}
