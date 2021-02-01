#include "utils/Moving.hpp"
#include "system/Interface.hpp"

Dot Moving::matrixDots[MAX_NUM_DOTS_MATRIX];

void Moving::initDots (void)
{
	for (int i = 0; i < MAX_NUM_DOTS_MATRIX; i++) {
		Moving::matrixDots[i].p.x = -1;
		Moving::matrixDots[i].p.y = -1;
		for (int j = 0; j < LAST_FIELDS_NUM; j++) {
			Moving::matrixDots[i].last[j].x = -1;
			Moving::matrixDots[i].last[j].y = -1;
		}
		Moving::matrixDots[i].outCounter = -1;
		Moving::matrixDots[i].bufferIndex = 0;
	}
}

void Moving::createDot (int x, int y)
{
	for (int i = 0; i < MAX_NUM_DOTS_MATRIX; i++) {
		if (Moving::matrixDots[i].outCounter != -1) continue;
		Moving::matrixDots[i].p.x = x;
		Moving::matrixDots[i].p.y = y;
		Moving::matrixDots[i].outCounter = 0;
		break;
	}
}

void Moving::createDot (int x, int y, Side origin)
{
	for (int i = 0; i < MAX_NUM_DOTS_MATRIX; i++) {
		if (Moving::matrixDots[i].outCounter != -1) continue;
		Moving::matrixDots[i].p.x = x;
		Moving::matrixDots[i].p.y = y;
		Moving::matrixDots[i].outCounter = 0;
		break;
	}
}

void Moving::autoResetDots (void)
{
	for (int i = 0; i < MAX_NUM_DOTS_MATRIX; i++) {
		if (Moving::matrixDots[i].outCounter == -1) continue;
		if (Maths::outOfBounds(Moving::matrixDots[i].p.x, Moving::matrixDots[i].p.y)) {
			if (Moving::matrixDots[i].outCounter >= OUT_COUNTER) {
				Moving::matrixDots[i].p.x = -1;
				Moving::matrixDots[i].p.y = -1;
				for (int j = 0; j < LAST_FIELDS_NUM; j++) {
					Moving::matrixDots[i].last[j].x = -1;
					Moving::matrixDots[i].last[j].y = -1;
				}
				Moving::matrixDots[i].outCounter = -1;
			}
			else Moving::matrixDots[i].outCounter++;
		}
	}
}

void Moving::updateBuffer (int index, Point p)
{
	Moving::matrixDots[index].last[Moving::matrixDots[index].bufferIndex] = p;
	Moving::matrixDots[index].bufferIndex == LAST_FIELDS_NUM - 1 ? Moving::matrixDots[index].bufferIndex = 0 : Moving::matrixDots[index].bufferIndex++;
}

void Moving::showDot (int i)
{
	if (Moving::matrixDots[i].outCounter == -1) return;
	for (int j = 0; j < LAST_FIELDS_NUM; j++) {
		CRGB weakC;
		weakC.r = ColorGradient::colors[Moving::matrixDots[i].last[j].x][Moving::matrixDots[i].last[j].y].r * WEAKEN_FACTOR;
		weakC.g = ColorGradient::colors[Moving::matrixDots[i].last[j].x][Moving::matrixDots[i].last[j].y].g * WEAKEN_FACTOR;
		weakC.b = ColorGradient::colors[Moving::matrixDots[i].last[j].x][Moving::matrixDots[i].last[j].y].b * WEAKEN_FACTOR;
		Interface::fadeToColor(Moving::matrixDots[i].last[j].x, Moving::matrixDots[i].last[j].y, weakC, FADE_FACTOR_DOTS);
	}
	if (!Maths::outOfBounds(Moving::matrixDots[i].p.x, Moving::matrixDots[i].p.y)) {
		Interface::ledOn(Moving::matrixDots[i].p.x, Moving::matrixDots[i].p.y, ColorGradient::colors[Moving::matrixDots[i].p.x][Moving::matrixDots[i].p.y]);
	}
}

void Moving::moveDot (int index, Direction dir)
{
	if (Maths::outOfBounds(Moving::matrixDots[index].p.x, Moving::matrixDots[index].p.y)) return;

	Point p = {
		.x = Moving::matrixDots[index].p.x,
		.y = Moving::matrixDots[index].p.y
	};
	Moving::updateBuffer(index, p);

	switch (dir) {
		case UP: {
			Moving::matrixDots[index].p.y++;
			break;
		}
		case DOWN: {
			Moving::matrixDots[index].p.y--;
			break;
		}
		case RIGHT: {
			Moving::matrixDots[index].p.x++;
			break;
		}
		case LEFT: {
			Moving::matrixDots[index].p.x--;
			break;
		}
		case UP_RIGHT: {
			Moving::matrixDots[index].p.x++;
			Moving::matrixDots[index].p.y++;
			break;
		}
		case UP_LEFT: {
			Moving::matrixDots[index].p.x--;
			Moving::matrixDots[index].p.y++;
			break;
		}
		case DOWN_RIGHT: {
			Moving::matrixDots[index].p.x++;
			Moving::matrixDots[index].p.y--;
			break;
		}
		case DOWN_LEFT: {
			Moving::matrixDots[index].p.x--;
			Moving::matrixDots[index].p.y--;
			break;
		}
		default: {
			break;
		}
	}
}
