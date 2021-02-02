#include "utils/Moving.hpp"
#include "system/Interface.hpp"

Dot Moving::dots[MAX_NUM_DOTS];
int Moving::activeDots = 0;
int Moving::maxNumDots = 0;

void Moving::resetDots (void)
{
	for (int i = 0; i < MAX_NUM_DOTS; i++) {
		Moving::dots[i].p.x = -1;
		Moving::dots[i].p.y = -1;
		for (int j = 0; j < LAST_FIELDS_NUM; j++) {
			Moving::dots[i].last[j].x = -1;
			Moving::dots[i].last[j].y = -1;
		}
		Moving::dots[i].outCounter = -1;
		Moving::dots[i].bufferIndex = 0;
	}
	Moving::activeDots = 0;
}

void Moving::createDot (int x, int y, Direction dir)
{
	if (Moving::activeDots >= Moving::maxNumDots) return;
	for (int i = 0; i < MAX_NUM_DOTS; i++) {
		if (Moving::dots[i].outCounter != -1) continue;
		Moving::dots[i].p.x = x;
		Moving::dots[i].p.y = y;
		Moving::dots[i].outCounter = 0;
		Moving::dots[i].dir = dir;
		break;
	}
	Moving::activeDots++;
}

void Moving::removeDot (Dot* dot)
{
	dot->p.x = -1;
	dot->p.y = -1;
}

void Moving::autoResetDot (Dot* dot)
{
	if (dot->outCounter == -1) return;
	if (Maths::outOfBounds(dot->p.x, dot->p.y)) {
		if (dot->outCounter >= LAST_FIELDS_NUM) {
			dot->p.x = -1;
			dot->p.y = -1;
			for (int j = 0; j < LAST_FIELDS_NUM; j++) {
				dot->last[j].x = -1;
				dot->last[j].y = -1;
			}
			dot->outCounter = -1;
			Moving::activeDots--;
		}
		else dot->outCounter++;
	}
}

void Moving::updateBuffer (Dot* dot)
{
	dot->last[dot->bufferIndex] = dot->p;
	dot->bufferIndex == LAST_FIELDS_NUM - 1 ? dot->bufferIndex = 0 : dot->bufferIndex++;
}

void Moving::showDot (Dot* dot)
{
	if (dot->outCounter == -1) return;
	for (int j = 0; j < LAST_FIELDS_NUM; j++) {
		CRGB weakC;
		weakC.r = ColorGradient::colors[dot->last[j].x][dot->last[j].y].r * WEAKEN_FACTOR;
		weakC.g = ColorGradient::colors[dot->last[j].x][dot->last[j].y].g * WEAKEN_FACTOR;
		weakC.b = ColorGradient::colors[dot->last[j].x][dot->last[j].y].b * WEAKEN_FACTOR;
		Interface::fadeToColor(dot->last[j].x, dot->last[j].y, weakC, FADE_FACTOR_DOTS);
	}
	if (!Maths::outOfBounds(dot->p.x, dot->p.y)) {
		Interface::ledOn(dot->p.x, dot->p.y, ColorGradient::colors[dot->p.x][dot->p.y]);
	}
}

void Moving::showDot (Dot* dot, CRGB color)
{
	if (dot->outCounter == -1) return;
	for (int j = 0; j < LAST_FIELDS_NUM; j++) {
		CRGB weakC;
		weakC.r = ColorGradient::colors[dot->last[j].x][dot->last[j].y].r * WEAKEN_FACTOR;
		weakC.g = ColorGradient::colors[dot->last[j].x][dot->last[j].y].g * WEAKEN_FACTOR;
		weakC.b = ColorGradient::colors[dot->last[j].x][dot->last[j].y].b * WEAKEN_FACTOR;
		Interface::fadeToColor(dot->last[j].x, dot->last[j].y, weakC, FADE_FACTOR_DOTS);
	}
	if (!Maths::outOfBounds(dot->p.x, dot->p.y)) {
		Interface::ledOn(dot->p.x, dot->p.y, color);
	}
}

void Moving::moveDot (Dot* dot)
{
	if (Maths::outOfBounds(dot->p.x, dot->p.y)) return;

	Moving::updateBuffer(dot);

	switch (dot->dir) {
		case UP: {
			dot->p.y++;
			break;
		}
		case DOWN: {
			dot->p.y--;
			break;
		}
		case RIGHT: {
			dot->p.x++;
			break;
		}
		case LEFT: {
			dot->p.x--;
			break;
		}
		case UP_RIGHT: {
			dot->p.x++;
			dot->p.y++;
			break;
		}
		case UP_LEFT: {
			dot->p.x--;
			dot->p.y++;
			break;
		}
		case DOWN_RIGHT: {
			dot->p.x++;
			dot->p.y--;
			break;
		}
		case DOWN_LEFT: {
			dot->p.x--;
			dot->p.y--;
			break;
		}
		default: {
			break;
		}
	}
}
