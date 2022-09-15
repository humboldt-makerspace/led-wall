#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "constants.h"
#include "Arduino.h"
#include "arduinoFFT.h"
#include "FastLED.h"
#include "WiFi.h"
#include "WiFiUdp.h"
#include "custom.h"

#include "utils/ColorGradient.hpp"
#include "utils/Mapping.hpp"
#include "utils/Bars.hpp"
#include "utils/Figures.hpp"
#include "utils/AudioAnalyzer.hpp"
#include "utils/Misc.hpp"
#include "utils/Moving.hpp"
#include "utils/CustomTypes.h"
#include "utils/MessageBoard.hpp"

#include "io/UDPManager.hpp"
#include "io/Parser.hpp"

class Interface {
private:
	/* variables */
	static int r;
	static int g;
	static int b;
	static boolean buttons[NUM_BUTTONS];

	/* functions */
	static void changeBrightness(void);
	static void changeMode(void);
	static void switchColors(void);

public:
	/* variables */
	static CRGB leds[NUM_DATA_PINS][NUM_LEDS];
	static uint8_t brightness;
	static boolean btnPressed[NUM_BUTTONS];
	static wall_mode_t mode;
	static color_mode_t cmode;

	/* functions */
	static void readButtons(void);
	static void ledOn(int x, int y, CRGB const &color);
	static void ledOff(int x, int y);
	static void fadeToColor(int x, int y, CRGB const &color, uint8_t fadefactor);
	static void allLedsOff(void);
	static void fadeOutAll(uint8_t fadefactor);
	static void statusLedOn(void);
	static void statusLedOff(void);
	static CRGB getColor(void);
	static void setMode(wall_mode_t newMode);
	static void setBrightness(uint8_t brightness);
	static void setColor(CRGB const &color);
	static void setColorMode(color_mode_t colorMode);
};

#endif
