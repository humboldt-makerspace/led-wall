#include "system/Interface.hpp"

boolean Interface::buttons[NUM_BUTTONS];
CRGB Interface::leds[NUM_DATA_PINS][NUM_LEDS];
uint8_t Interface::brightness;
boolean Interface::btnPressed[NUM_BUTTONS];
WallMode Interface::mode;
ColorMode Interface::cmode;

int Interface::r = 0;
int Interface::g = 255;
int Interface::b = 0;

void Interface::ledOn (int x, int y, CRGB color)
{
	if (Misc::outOfBounds(x, y)) return;
	int pos = Mapping::getPos(x, y);
	int block = Mapping::getBlock(y);
	Interface::leds[block][pos] = color;
}

void Interface::ledOff (int x, int y)
{
	if (Misc::outOfBounds(x, y)) return;
	int pos = Mapping::getPos(x, y);
	int block = Mapping::getBlock(y);
	Interface::leds[block][pos] = CRGB::Black;
}

void Interface::fadeToColor (int x, int y, CRGB color, uint8_t fadefactor)
{
	if (Misc::outOfBounds(x, y)) return;
	int pos = Mapping::getPos(x, y);
	int block = Mapping::getBlock(y);
	nblend(Interface::leds[block][pos], color, fadefactor);
}

void Interface::allLedsOff (void)
{
	for (int i = 0; i < NUM_DATA_PINS; i++) {
		for (int j = 0; j < NUM_LEDS; j++) {
			Interface::leds[i][j] = CRGB::Black;
		}
	}
}

void Interface::fadeOutAll (uint8_t fadefactor)
{
	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = 0; j < WALL_HEIGHT; j++) {
			Interface::fadeToColor(i, j, CRGB::Black, fadefactor);
		}
	}
}

void Interface::statusLedOn (void)
{
	digitalWrite(STATUS_LED_PIN, HIGH);
}

void Interface::statusLedOff (void)
{
	digitalWrite(STATUS_LED_PIN, LOW);
}

CRGB Interface::getColor (void)
{
	return CRGB(r, g, b);
}

void Interface::setColor (CRGB color)
{
	Interface::r = color.r;
	Interface::g = color.g;
	Interface::b = color.b;
}

void Interface::changeBrightness (void)
{
	if (brightness == 0) brightness = 255;
	else brightness -= BRIGHTNESS_DEC;

	if (brightness < 0) brightness = 0;
	FastLED.setBrightness(brightness);
}

void Interface::setBrightness (uint8_t brightness)
{
	Interface::brightness = brightness;
	FastLED.setBrightness(brightness);
}

void initColors (void)
{
	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = 0; j < WALL_HEIGHT; j++) {
			CRGB weakC;
			weakC.r = ColorGradient::colors[i][j].r * WEAKEN_FACTOR;
			weakC.g = ColorGradient::colors[i][j].g * WEAKEN_FACTOR;
			weakC.b = ColorGradient::colors[i][j].b * WEAKEN_FACTOR;
			Interface::ledOn(i, j, weakC);
		}
	}
}

void initModes (WallMode mode)
{
	switch (mode) {
		case LIGHT_SHOW_LOOP: {
			MessageBoard::showMessage("loop", QUICK_NOTE_DURATION);
			initColors();
			Moving::resetDots();
			for (int i = 0; i < MAX_NUM_DOTS_CIRCLE; i++) {
				Moving::dots[i].p.x = i;
				Moving::dots[i].p.y = i;
				Moving::dots[i].outCounter = 0;
				Moving::dots[i].dir = UP;
			}
			break;
		}
		case LIGHT_SHOW_MATRIX_VIBE: {
			MessageBoard::showMessage("matrix", QUICK_NOTE_DURATION);
			initColors();
			Moving::resetDots();
			Moving::maxNumDots = MAX_NUM_DOTS_MATRIX;
			break;
		}
		case LIGHT_SHOW_PROCESSOR: {
			MessageBoard::showMessage("processor", QUICK_NOTE_DURATION);
			initColors();
			Moving::resetDots();
			Moving::maxNumDots = MAX_NUM_DOTS_PROCESSOR;
			break;
		}
		case LIGHT_SHOW_NETWORK: {
			MessageBoard::showMessage("network", QUICK_NOTE_DURATION);
			initColors();
			Moving::resetDots();
			Moving::maxNumDots = MAX_NUM_DOTS_NETWORK;
			break;
		}
		case LIGHT_SHOW_PRIDE: {
			MessageBoard::showMessage("pride", QUICK_NOTE_DURATION);
			break;
		}
		case LIGHT_SHOW_STATIC_COLOR: {
			MessageBoard::showMessage("static", QUICK_NOTE_DURATION);
			break;
		}
		case CLOCK_DIGITAL: {
			MessageBoard::showMessage("clock digit", QUICK_NOTE_DURATION);
			break;
		}
		case CLOCK_WORD: {
			MessageBoard::showMessage("clock word", QUICK_NOTE_DURATION);
			break;
		}
		case AUDIO_VISUALIZER: {
			MessageBoard::showMessage("audio", QUICK_NOTE_DURATION);
			break;
		}
		case MESSAGE_BOARD: {
			MessageBoard::showMessage("message", QUICK_NOTE_DURATION);
			break;
		}
		case TEST: {
			MessageBoard::showMessage("test", QUICK_NOTE_DURATION);
			break;
		}
		default: {
			break;
		}
	}
}

void Interface::changeMode (void)
{
	if (mode == WallMode::AUDIO_VISUALIZER) mode = WallMode::LIGHT_SHOW_PRIDE;
	else {
		int tmp = (int) mode;
		tmp++;
		mode = (WallMode) tmp;
	}
	initModes(mode);
	Interface::allLedsOff();
}

void Interface::setMode (WallMode mode)
{
	Interface::mode = mode;
	initModes(mode);
	Interface::allLedsOff();
}

void Interface::switchColors (void)
{
	if (cmode == ColorMode::MONO) {
		if (g == 255 && r < 255 && !b) r += COLOR_INC;
		else if (g > 0 && r == 255 && !b) g -= COLOR_INC;
		else if (r == 255 && b < 255 && !g) b += COLOR_INC;
		else if (r > 0 && b == 255 && !g) r -= COLOR_INC;
		else if (b == 255 && g < 255 && !r) g += COLOR_INC;
		else if (b > 0 && g == 255 && !r) b -= COLOR_INC;

		if (r > 255) r = 255;
		else if (r < 0) r = 0;
		if (g > 255) g = 255;
		else if (g < 0) g = 0;
		if (b > 255) b = 255;
		else if (b < 0) b = 0;

		if (g == 255 && !r && !b) cmode = ColorMode::RAINBOW_HORIZONTAL;
	}
	else {
		int tmp = (int) cmode;
		tmp++;
		cmode = (ColorMode) tmp;
	}
	ColorGradient::changeColorGradient(cmode);
}

void Interface::setColorMode (ColorMode cmode)
{
	Interface::cmode = cmode;
	ColorGradient::changeColorGradient(cmode);
}

void Interface::readButtons (void)
{
	buttons[0] = digitalRead(BUTTON_1_PIN);
	buttons[1] = digitalRead(BUTTON_2_PIN);
	buttons[2] = digitalRead(BUTTON_3_PIN);

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (!buttons[i]) btnPressed[i] = true;
	}
	if (buttons[0] && btnPressed[0]) {
		btnPressed[0] = false;
		changeBrightness();
	}
	if (buttons[1] && btnPressed[1]) {
		btnPressed[1] = false;
		changeMode();
	}
	if (buttons[2] && btnPressed[2]) {
		btnPressed[2] = false;
		switchColors();
	}
}
