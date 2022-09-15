#include "includes.h"

String inc;
String lastMsg;

void setup(void)
{
	Setup::init();
	AudioVisualizer::flushBuffer();
	MessageBoard::initColorSet();
	AudioVisualizer::init();
}

void loop(void)
{
	Interface::readButtons();
	//inc = UDPManager::readPackage();
	//UDPManager::processCommand(inc);
	//MessageBoard::showMessage(inc, MSG_DURATION);
	//if (!inc.isEmpty() && inc.charAt(0) != '/') lastMsg = inc;

	switch (Interface::mode) {
		case LIGHT_SHOW_PRIDE: {
			LightShow::pride();
			break;
		}
		case LIGHT_SHOW_STATIC_COLOR: {
			LightShow::staticColor();
			break;
		}
		case LIGHT_SHOW_MATRIX_VIBE: {
			LightShow::matrixVibe();
			break;
		}
		case LIGHT_SHOW_PROCESSOR: {
			LightShow::processorAnimation();
			break;
		}
		case LIGHT_SHOW_LOOP: {
			LightShow::looping();
			break;
		}
		case LIGHT_SHOW_NETWORK: {
			LightShow::networkAnimation();
			break;
		}
		case CLOCK_DIGITAL: {
			Clock::showTimeDigits();
			break;
		}
		case CLOCK_WORD: {
			Clock::showTimeWords();
			break;
		}
		case MESSAGE_BOARD: {
			MessageBoard::shiftMessage(lastMsg);
			break;
		}
		case AUDIO_VISUALIZER: {
			AudioVisualizer::visualizeAudio();
			break;
		}
		case TEST: {
			Interface::allLedsOff();
			break;
		}
		default: {
			break;
		}
	}

	FastLED.show();
	// int port = 2;
	// Serial.print("Port: ");
	// Serial.print(port);
	// Serial.print(" ");
	// Serial.println(analogRead(port));
}
