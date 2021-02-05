#include "utils/Figures.hpp"
#include "system/Interface.hpp"

boolean Figures::alphabet[NUM_FIGURES][FIGURE_WIDTH][FIGURE_HEIGHT];
boolean Figures::numbers[NUM_BIG_NUM][BIG_NUM_WIDTH][BIG_NUM_HEIGHT];

Figure Figures::charToFigure (char c)
{
	switch (c) {
		case 'a':
		case 'A': return A;
		case 'b':
		case 'B': return B;
		case 'c':
		case 'C': return C;
		case 'd':
		case 'D': return D;
		case 'e':
		case 'E': return E;
		case 'f':
		case 'F': return F;
		case 'g':
		case 'G': return G;
		case 'h':
		case 'H': return H;
		case 'i':
		case 'I': return I;
		case 'j':
		case 'J': return J;
		case 'k':
		case 'K': return K;
		case 'l':
		case 'L': return L;
		case 'm':
		case 'M': return M;
		case 'n':
		case 'N': return N;
		case 'o':
		case 'O': return O;
		case 'p':
		case 'P': return P;
		case 'q':
		case 'Q': return Q;
		case 'r':
		case 'R': return R;
		case 's':
		case 'S': return S;
		case 't':
		case 'T': return T;
		case 'u':
		case 'U': return U;
		case 'v':
		case 'V': return V;
		case 'w':
		case 'W': return W;
		case 'x':
		case 'X': return X;
		case 'y':
		case 'Y': return Y;
		case 'z':
		case 'Z': return Z;
		case '!': return EXC;
		case '?': return QUEST;
		case ' ': return SPACE;
		default: return N0;
	}
}

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
			switch (y) {
				case 0: {
					if (x == 0 || x == 4) {
						alphabet[A][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[M][x][y] = true;
						alphabet[N][x][y] = true;
						alphabet[R][x][y] = true;
						alphabet[X][x][y] = true;
						alphabet[K][x][y] = true;
					}
					if (x >= 0 && x < 4) {
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[S][x][y] = true;
						alphabet[N5][x][y] = true;
					}
					if (x > 0 && x <= 4) {
						alphabet[C][x][y] = true;
						alphabet[S][x][y] = true;
					}
					if (x >= 0 && x <= 4) {
						alphabet[E][x][y] = true;
						alphabet[L][x][y] = true;
						alphabet[Z][x][y] = true;
						alphabet[N2][x][y] = true;
					}
					if (x == 0) {
						alphabet[F][x][y] = true;
						alphabet[P][x][y] = true;
					}
					if (x > 0 && x < 4) {
						alphabet[G][x][y] = true;
						alphabet[I][x][y] = true;
						alphabet[J][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[N0][x][y] = true;
						alphabet[N1][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N6][x][y] = true;
						alphabet[N8][x][y] = true;
						alphabet[N9][x][y] = true;
					}
					if (x != 0 && x != 3) {
						alphabet[Q][x][y] = true;
					}
					if (x == 2) {
						alphabet[T][x][y] = true;
						alphabet[V][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[N7][x][y] = true;
						alphabet[EXC][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x == 1 || x == 3) {
						alphabet[W][x][y] = true;
					}
					if (x == 4) {
						alphabet[N4][x][y] = true;
					}
					break;
				}
				case 1: {
					if (x == 0 || x == 4) {
						alphabet[A][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[M][x][y] = true;
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[G][x][y] = true;
						alphabet[J][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[X][x][y] = true;
						alphabet[N0][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N6][x][y] = true;
						alphabet[N8][x][y] = true;
						alphabet[N9][x][y] = true;
					}
					if (x == 0) {
						alphabet[C][x][y] = true;
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[L][x][y] = true;
						alphabet[P][x][y] = true;
						alphabet[Z][x][y] = true;
					}
					if (x == 2) {
						alphabet[I][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[N1][x][y] = true;
						alphabet[N7][x][y] = true;
					}
					if (x == 0 || x == 3) {
						alphabet[K][x][y] = true;
						alphabet[Q][x][y] = true;
						alphabet[R][x][y] = true;
					}
					if (x != 1 && x != 2) {
						alphabet[N][x][y] = true;
					}
					if (x == 4) {
						alphabet[S][x][y] = true;
						alphabet[N4][x][y] = true;
						alphabet[N5][x][y] = true;
					}
					if (x > 0 && x < 4) {
						alphabet[V][x][y] = true;
					}
					if (x != 1 && x != 3) {
						alphabet[W][x][y] = true;
					}
					if (x == 1) {
						alphabet[N2][x][y] = true;
					}
					break;
				}
				case 2: {
					if (x == 0 || x == 4) {
						alphabet[A][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[M][x][y] = true;
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[G][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[N6][x][y] = true;
						alphabet[N8][x][y] = true;
					}
					if (x == 0) {
						alphabet[C][x][y] = true;
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[L][x][y] = true;
						alphabet[P][x][y] = true;
					}
					if (x == 2) {
						alphabet[I][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[N1][x][y] = true;
						alphabet[N2][x][y] = true;
						alphabet[N7][x][y] = true;
						alphabet[EXC][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x == 4) {
						alphabet[J][x][y] = true;
						alphabet[S][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N4][x][y] = true;
						alphabet[N5][x][y] = true;
						alphabet[N9][x][y] = true;
					}
					if (x == 0 || x == 2) {
						alphabet[K][x][y] = true;
						alphabet[R][x][y] = true;
					}
					if (x != 1) {
						alphabet[N][x][y] = true;
					}
					if (x != 1 && x != 3) {
						alphabet[Q][x][y] = true;
						alphabet[W][x][y] = true;
					}
					if (x != 2) {
						alphabet[V][x][y] = true;
					}
					if (x == 1 || x == 3) {
						alphabet[X][x][y] = true;
					}
					if (x == 1) {
						alphabet[Z][x][y] = true;
					}
					if (x != 2 && x != 3) {
						alphabet[N0][x][y] = true;
					}
					break;
				}
				case 3: {
					if (x == 0 || x == 4) {
						alphabet[M][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[Q][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[V][x][y] = true;
					}
					if (x >= 0 && x <= 4) {
						alphabet[A][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[N4][x][y] = true;
					}
					if (x >= 0 && x < 4) {
						alphabet[B][x][y] = true;
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[P][x][y] = true;
						alphabet[R][x][y] = true;
						alphabet[N5][x][y] = true;
						alphabet[N6][x][y] = true;
					}
					if (x == 0) {
						alphabet[C][x][y] = true;
						alphabet[L][x][y] = true;
					}
					if (x != 1) {
						alphabet[G][x][y] = true;
					}
					if (x == 2) {
						alphabet[I][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[X][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[Z][x][y] = true;
						alphabet[N1][x][y] = true;
						alphabet[EXC][x][y] = true;
					}
					if (x == 4) {
						alphabet[J][x][y] = true;
					}
					if (x == 0 || x == 1) {
						alphabet[K][x][y] = true;
					}
					if (x != 1 && x != 3) {
						alphabet[N][x][y] = true;
						alphabet[W][x][y] = true;
						alphabet[N0][x][y] = true;
					}
					if (x > 0 && x < 4) {
						alphabet[S][x][y] = true;
						alphabet[N8][x][y] = true;
					}
					if (x == 3) {
						alphabet[N2][x][y] = true;
						alphabet[N7][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x == 2 || x == 3) {
						alphabet[N3][x][y] = true;
					}
					if (x > 0 && x <= 4) {
						alphabet[N9][x][y] = true;
					}
					break;
				}
				case 4: {
					if (x == 0 || x == 4) {
						alphabet[A][x][y] = true;
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[P][x][y] = true;
						alphabet[Q][x][y] = true;
						alphabet[R][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[V][x][y] = true;
						alphabet[N4][x][y] = true;
						alphabet[N8][x][y] = true;
						alphabet[N9][x][y] = true;
					}
					if (x == 0) {
						alphabet[C][x][y] = true;
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[G][x][y] = true;
						alphabet[L][x][y] = true;
						alphabet[S][x][y] = true;
						alphabet[N5][x][y] = true;
						alphabet[N6][x][y] = true;
					}
					if (x == 2) {
						alphabet[I][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[N1][x][y] = true;
						alphabet[EXC][x][y] = true;
					}
					if (x == 4) {
						alphabet[J][x][y] = true;
						alphabet[N2][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N7][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x == 0 || x == 2) {
						alphabet[K][x][y] = true;
					}
					if (x != 1 && x != 3) {
						alphabet[M][x][y] = true;
						alphabet[W][x][y] = true;
					}
					if (x != 3) {
						alphabet[N][x][y] = true;
					}
					if (x == 1 || x == 3) {
						alphabet[X][x][y] = true;
					}
					if (x == 3) {
						alphabet[Z][x][y] = true;
					}
					if (x != 1 && x != 2) {
						alphabet[N0][x][y] = true;
					}
					break;
				}
				case 5: {
					if (x == 0 || x == 4) {
						alphabet[A][x][y] = true;
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[H][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[P][x][y] = true;
						alphabet[Q][x][y] = true;
						alphabet[R][x][y] = true;
						alphabet[S][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[V][x][y] = true;
						alphabet[W][x][y] = true;
						alphabet[X][x][y] = true;
						alphabet[N0][x][y] = true;
						alphabet[N2][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N4][x][y] = true;
						alphabet[N6][x][y] = true;
						alphabet[N8][x][y] = true;
						alphabet[N9][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x == 0) {
						alphabet[C][x][y] = true;
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[G][x][y] = true;
						alphabet[L][x][y] = true;
						alphabet[N5][x][y] = true;
					}
					if (x == 2) {
						alphabet[I][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[EXC][x][y] = true;
					}
					if (x == 4) {
						alphabet[J][x][y] = true;
						alphabet[Z][x][y] = true;
						alphabet[N7][x][y] = true;
					}
					if (x == 0 || x == 3) {
						alphabet[K][x][y] = true;
					}
					if (x != 2) {
						alphabet[M][x][y] = true;
					}
					if (x != 2 && x != 3) {
						alphabet[N][x][y] = true;
					}
					if (x == 1 || x == 3) {
						alphabet[Y][x][y] = true;
					}
					if (x == 1 || x == 2) {
						alphabet[N1][x][y] = true;
					}
					break;
				}
				case 6: {
					if (x > 0 && x < 4) {
						alphabet[A][x][y] = true;
						alphabet[I][x][y] = true;
						alphabet[O][x][y] = true;
						alphabet[Q][x][y] = true;
						alphabet[N0][x][y] = true;
						alphabet[N2][x][y] = true;
						alphabet[N3][x][y] = true;
						alphabet[N6][x][y] = true;
						alphabet[N8][x][y] = true;
						alphabet[N9][x][y] = true;
						alphabet[QUEST][x][y] = true;
					}
					if (x >= 0 && x < 4) {
						alphabet[B][x][y] = true;
						alphabet[D][x][y] = true;
						alphabet[P][x][y] = true;
						alphabet[R][x][y] = true;
					}
					if (x > 0 && x <= 4) {
						alphabet[C][x][y] = true;
						alphabet[G][x][y] = true;
						alphabet[S][x][y] = true;
					}
					if (x >= 0 && x <= 4) {
						alphabet[E][x][y] = true;
						alphabet[F][x][y] = true;
						alphabet[J][x][y] = true;
						alphabet[T][x][y] = true;
						alphabet[Z][x][y] = true;
						alphabet[N5][x][y] = true;
						alphabet[N7][x][y] = true;
					}
					if (x == 0 || x == 4) {
						alphabet[H][x][y] = true;
						alphabet[K][x][y] = true;
						alphabet[M][x][y] = true;
						alphabet[N][x][y] = true;
						alphabet[U][x][y] = true;
						alphabet[V][x][y] = true;
						alphabet[W][x][y] = true;
						alphabet[X][x][y] = true;
						alphabet[Y][x][y] = true;
						alphabet[N4][x][y] = true;
					}
					if (x == 0) {
						alphabet[L][x][y] = true;
					}
					if (x == 2) {
						alphabet[N1][x][y] = true;
						alphabet[EXC][x][y] = true;
					}
					break;
				}
				default: {
					break;
				}
			}
		}
	}
}

void Figures::defineNumbers (void)
{
	for (int i = 0; i < NUM_BIG_NUM; i++) {
		for (int x = 0; x < BIG_NUM_WIDTH; x++) {
			for (int y = 0; y < BIG_NUM_HEIGHT; y++) {
				numbers[i][x][y] = false;
			}
		}
	}

	for (int x = 0; x < BIG_NUM_WIDTH; x++) {
		for (int y = 0; y < BIG_NUM_HEIGHT; y++) {
			/* 0 */
			if (y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2 ||
				x == 0 ||
				x == 1 ||
				x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2) numbers[Z0][x][y] = true;

			/* 1 */
			if (x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2) numbers[Z1][x][y] = true;

			/* 2 */
			if (((x == 0 || x == 1) && y < BIG_NUM_HEIGHT / 2) ||
				((x == BIG_NUM_WIDTH - 1 || x == BIG_NUM_WIDTH - 2) && y > BIG_NUM_HEIGHT / 2) ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z2][x][y] = true;

			/* 3 */
			if (x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z3][x][y] = true;

			/* 4 */
			if (x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2 ||
				((x == 0 || x == 1) && y > BIG_NUM_HEIGHT / 2) ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1) numbers[Z4][x][y] = true;

			/* 5 */
			if (((x == 0 || x == 1) && y > BIG_NUM_HEIGHT / 2) ||
				((x == BIG_NUM_WIDTH - 1 || x == BIG_NUM_WIDTH - 2) && y < BIG_NUM_HEIGHT / 2) ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z5][x][y] = true;
			
			/* 6 */
			if (x == 0 ||
				x == 1 ||
				((x == BIG_NUM_WIDTH - 1 || x == BIG_NUM_WIDTH - 2) && y < BIG_NUM_HEIGHT / 2) ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z6][x][y] = true;
			
			/* 7 */
			if (x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z7][x][y] = true;

			/* 8 */
			if (x == 0 ||
				x == 1 ||
				x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2 ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2) numbers[Z8][x][y] = true;

			/* 9 */
			if (x == BIG_NUM_WIDTH - 1 ||
				x == BIG_NUM_WIDTH - 2 ||
				y == 0 ||
				y == 1 ||
				y == BIG_NUM_HEIGHT / 2 ||
				y == BIG_NUM_HEIGHT / 2 - 1 ||
				y == BIG_NUM_HEIGHT - 1 ||
				y == BIG_NUM_HEIGHT - 2 ||
				((x == 0 || x == 1) && y > BIG_NUM_HEIGHT / 2)) numbers[Z9][x][y] = true;
		}
	}
}

void Figures::displayColon (int x, int y)
{	
	Interface::ledOn(x, y, ColorGradient::colors[x][y]);
	Interface::ledOn(x, y + 3, ColorGradient::colors[x][y + 3]);
}

void Figures::displayNumber (BigNumber number, int x, int y)
{
	for (int i = 0; i < BIG_NUM_WIDTH; i++) {
		for (int j = 0; j < BIG_NUM_HEIGHT; j++) {
			if (!numbers[number][i][j]) Interface::fadeToColor(x + i, y + j, CRGB::Black, FADE_FACTOR_CLOCK);
			else Interface::fadeToColor(x + i, y + j, ColorGradient::colors[x + i][y + j], FADE_FACTOR_CLOCK);
		}
	}
}

void Figures::displayFigure (Figure figure, int x, int y)
{
	for (int i = 0; i < FIGURE_WIDTH; i++) {
		for (int j = 0; j < FIGURE_HEIGHT; j++) {
			if (!alphabet[figure][i][j]) Interface::fadeToColor(x + i, y + j, CRGB::Black, FADE_FACTOR_FIGURE);
			else Interface::fadeToColor(x + i, y + j, ColorGradient::colors[x + i][y + j], FADE_FACTOR_FIGURE);
		}
	}
}

void Figures::displayFigureMono (Figure figure, int x, int y, CRGB color)
{
	for (int i = 0; i < FIGURE_WIDTH; i++) {
		for (int j = 0; j < FIGURE_HEIGHT; j++) {
			if (!alphabet[figure][i][j]) Interface::fadeToColor(x + i, y + j, CRGB::Black, FADE_FACTOR_FIGURE);
			else Interface::fadeToColor(x + i, y + j, color, FADE_FACTOR_FIGURE);
		}
	}
}
