#include "includes.h"

String inc;

void setup ()
{
	Setup::init();
	AudioVisualizer::flushBuffer();
	MessageBoard::initColorSet();
}

void loop ()
{	
	Interface::readButtons();
	inc = UDPManager::readPackage();
	UDPManager::processCommand(inc);
	MessageBoard::showMessage(inc);

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
		case CLOCK: {
			Clock::showTime();
			break;
		}
		case AUDIO_VISUALIZER: {
			AudioVisualizer::visualizeAudio();
			break;
		}
		case TEST: {
			MessageBoard::letterShiftTest();
			//Interface::allLedsOff();
			break;
		}
		default: {
			break;
		}
	}
	FastLED.show();
}
