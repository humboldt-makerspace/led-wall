#include "utils/Moving.hpp"
#include "features/LightShow.hpp"
#include "system/Interface.hpp"

void LightShow::pride (void)
{
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88(87, 220, 250);
	uint8_t brightdepth = beatsin88(341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis ;
	sLastMillis = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400, 5, 9);
	uint16_t brightnesstheta16 = sPseudotime;

	for (uint16_t i = 0; i < NUM_LEDS; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV(hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS - 1) - pixelnumber;

		nblend(Interface::leds[0][pixelnumber], newcolor, 64);
		nblend(Interface::leds[1][pixelnumber], newcolor, 64);
		nblend(Interface::leds[2][pixelnumber], newcolor, 64);
	}
}

void LightShow::staticColor (void)
{
	for (int x = 0; x < WALL_WIDTH; x++) {
		for (int y = 0; y < WALL_HEIGHT; y++) {
			Interface::ledOn(x, y, ColorGradient::colors[x][y]);
		}
	}
}

void LightShow::matrixVibe (void)
{
	int col = rand() % 70;
	if (col < WALL_WIDTH) Moving::createDot(col, WALL_HEIGHT - 1, DOWN);
	for (int i = 0; i < Moving::maxNumDots; i++) {
		Moving::showDot(&Moving::dots[i]);
		Moving::moveDot(&Moving::dots[i]);
		Moving::autoResetDot(&Moving::dots[i]);
	}
	delay(40);
}

void LightShow::EKGPulse (void)
{
	
}

bool insideProcessor (int x, int y)
{
	return (x >= WALL_WIDTH / 2 - PROCESSOR_SIZE / 2 &&
			x < WALL_WIDTH / 2 + PROCESSOR_SIZE / 2 &&
			y >= WALL_HEIGHT / 2 - PROCESSOR_SIZE / 2 &&
			y < WALL_HEIGHT / 2 + PROCESSOR_SIZE / 2);
}

bool onProcessorEdge (int x, int y)
{
	if ((x == WALL_WIDTH / 2 - PROCESSOR_SIZE / 2 - 1 && y == WALL_HEIGHT / 2 - PROCESSOR_SIZE / 2 - 1) ||
		(x == WALL_WIDTH / 2 - PROCESSOR_SIZE / 2 - 1 && y == WALL_HEIGHT / 2 + PROCESSOR_SIZE / 2) ||
		(x == WALL_WIDTH / 2 + PROCESSOR_SIZE / 2 && y == WALL_HEIGHT / 2 - PROCESSOR_SIZE / 2 - 1) ||
		(x == WALL_WIDTH / 2 + PROCESSOR_SIZE / 2 && y == WALL_HEIGHT / 2 + PROCESSOR_SIZE / 2)) {
			return false;
	}
	return (x >= WALL_WIDTH / 2 - PROCESSOR_SIZE / 2 - 1 &&
			x <= WALL_WIDTH / 2 + PROCESSOR_SIZE / 2 &&
			y >= WALL_HEIGHT / 2 - PROCESSOR_SIZE / 2 - 1 &&
			y <= WALL_HEIGHT / 2 + PROCESSOR_SIZE / 2) && !insideProcessor(x, y);
}

void showProcessor (void)
{
	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = 0; j < WALL_HEIGHT; j++) {
			if (onProcessorEdge(i, j)) {
				Interface::ledOn(i, j, CRGB(7, 7, 7));
			}
		}
	}
}

void LightShow::processorAnimation (void)
{
	showProcessor();
	int randSide = rand() % 4;
	int randInd;
	randInd = randSide % 2 == 0 ? rand() % PROCESSOR_SIZE + WALL_WIDTH / 2 - PROCESSOR_SIZE / 2 :
								  rand() % PROCESSOR_SIZE + WALL_HEIGHT / 2 - PROCESSOR_SIZE / 2;
	switch (randSide) {
		case 0: {
			Moving::createDot(randInd, WALL_HEIGHT - 1, DOWN);
			break;
		}
		case 1: {
			Moving::createDot(WALL_WIDTH - 1, randInd, LEFT);
			break;
		}
		case 2: {
			Moving::createDot(randInd, 0, UP);
			break;
		}
		case 3: {
			Moving::createDot(0, randInd, RIGHT);
			break;
		}
		default: {
			break;
		}
	}
	for (int i = 0; i < Moving::maxNumDots; i++) {
		if (insideProcessor(Moving::dots[i].p.x, Moving::dots[i].p.y)) {
			Moving::removeDot(&Moving::dots[i]);
		}
		if (onProcessorEdge(Moving::dots[i].p.x, Moving::dots[i].p.y)) {
			Moving::showDot(&Moving::dots[i], CRGB::White);
		}
		else Moving::showDot(&Moving::dots[i]);

		Moving::moveDot(&Moving::dots[i]);
		Moving::autoResetDot(&Moving::dots[i]);
	}
}

void changeDirectionLoop (Dot* dot, int i)
{
	if (dot->p.x >= WALL_WIDTH - 1 - i && dot->p.y > 0 + i) {
		dot->dir = DOWN;
	}
	else if (dot->p.y <= 0 + i && dot->p.x > 0 + i) {
		dot->dir = LEFT;
	}
	else if (dot->p.x <= 0 + i && dot->p.y < WALL_HEIGHT - 1 - i) {
		dot->dir = UP;
	}
	else if (dot->p.y >= WALL_HEIGHT - 1 - i && dot->p.x < WALL_WIDTH - 1 - i) {
		dot->dir = RIGHT;
	}
}

void LightShow::looping (void)
{
	for (int i = 0; i < Moving::maxNumDots; i++) {
		changeDirectionLoop(&Moving::dots[i], i);
		Moving::showDot(&Moving::dots[i]);
		Moving::moveDot(&Moving::dots[i]);
	}
}

void LightShow::networkAnimation (void)
{
	int randSide = rand() % 4;
	int randInd;
	randInd = randSide % 2 == 0 ? rand() % WALL_WIDTH : rand() % WALL_HEIGHT;
	switch (randSide) {
		case 0: {
			Moving::createDot(randInd, WALL_HEIGHT - 1, DOWN);
			break;
		}
		case 1: {
			Moving::createDot(WALL_WIDTH - 1, randInd, LEFT);
			break;
		}
		case 2: {
			Moving::createDot(randInd, 0, UP);
			break;
		}
		case 3: {
			Moving::createDot(0, randInd, RIGHT);
			break;
		}
		default: {
			break;
		}
	}
	for (int i = 0; i < Moving::maxNumDots; i++) {
		Moving::showDot(&Moving::dots[i]);
		Moving::moveDot(&Moving::dots[i]);
		Moving::autoResetDot(&Moving::dots[i]);
	}
}
