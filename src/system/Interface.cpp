#include "system/Interface.hpp"

boolean Interface::buttons[NUM_BUTTONS];
CRGB Interface::leds[NUM_DATA_PINS][NUM_LEDS];
uint8_t Interface::brightness;
boolean Interface::btnPressed[NUM_BUTTONS];
WallMode Interface::mode;
ColorMode Interface::cmode;

/* NOTE: the order is GRB */
int Interface::r = 0;
int Interface::g = 255;
int Interface::b = 0;

void Interface::ledOn (int x, int y, CRGB color)
{
	int pos = Mapping::getPos(x, y);
	int block = Mapping::getBlock(y);
	Interface::leds[block][pos] = color;
}

void Interface::ledOff (int x, int y)
{
	int pos = Mapping::getPos(x, y);
	int block = Mapping::getBlock(y);
	Interface::leds[block][pos] = CRGB::Black;
}

void Interface::fadeToColor (int x, int y, CRGB color, uint8_t fadefactor)
{
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

void Interface::fadeOutAll (void)
{
	for (int i = 0; i < NUM_DATA_PINS; i++) {
		for (int j = 0; j < NUM_LEDS; j++) {
			Interface::fadeToColor(i, j, CRGB::Black, FADE_FACTOR_OFF);
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
	return CRGB(g, r, b);
}

void Interface::changeBrightness (void)
{
	if (brightness == 0) brightness = 255;
	else brightness -= BRIGHTNESS_DEC;

	if (brightness < 0) brightness = 0;
	FastLED.setBrightness(brightness);
}

void Interface::changeMode (void)
{
	if (mode == WallMode::AUDIO_VISUALIZER) mode = WallMode::LIGHT_SHOW_PRIDE;
	else {
		int tmp = (int) mode;
		tmp++;
		mode = (WallMode) tmp;
	}
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
