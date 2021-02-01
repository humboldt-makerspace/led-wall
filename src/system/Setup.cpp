#include "system/Setup.hpp"
#include "system/Interface.hpp"

WiFiUDP Setup::UDPServer;

void initStatusLed (void)
{
	pinMode(STATUS_LED_PIN, OUTPUT);
	digitalWrite(STATUS_LED_PIN, HIGH);
	delay(200);
	digitalWrite(STATUS_LED_PIN, LOW);
}

void initButtons (void)
{
	pinMode(BUTTON_1_PIN, INPUT_PULLUP);
	pinMode(BUTTON_2_PIN, INPUT_PULLUP);
	pinMode(BUTTON_3_PIN, INPUT_PULLUP);
	for (int i = 0; i < NUM_BUTTONS; i++) Interface::btnPressed[i] = false;
}

void initLeds (void)
{
	FastLED.addLeds<WS2812B, LED_PIN_1>(Interface::leds[0], NUM_LEDS);
	FastLED.addLeds<WS2812B, LED_PIN_2>(Interface::leds[1], NUM_LEDS);
	FastLED.addLeds<WS2812B, LED_PIN_3>(Interface::leds[2], NUM_LEDS);
}

void initWallStatus (void)
{
	Interface::mode = WallMode::LIGHT_SHOW_PRIDE;
	Interface::cmode = ColorMode::RAINBOW_HORIZONTAL;
	Interface::brightness = 255;
	ColorGradient::changeColorGradient(Interface::cmode);
	Figures::defineAlphabet();
	Moving::initDots();
}

void Setup::initWifi (void)
{
	Serial.print("MAC: ");
	Serial.println(WiFi.macAddress());

	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID_CUSTOM, PW_CUSTOM);
	Serial.println();
	Serial.println();
	Serial.print("Wait for WiFi... ");

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Setup::UDPServer.begin(UDP_PORT);

	
	configTime(TIME_ZONE * 3600, DST * 0, NTP_SERVER);
  	Serial.println("\nWaiting for time");
  	while (!time(nullptr)) {
    	Serial.print(".");
    	delay(1000);
  	}
  	Serial.println("");
	time_t now = time(nullptr);
  	Serial.println(ctime(&now));
}

void Setup::init (void)
{
	Serial.begin(115200);
	initWifi();
	initButtons();
	initLeds();
	initWallStatus();
	initStatusLed();
}
