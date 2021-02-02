#include "includes.hpp"

void setup ()
{
	Setup::init();
	AudioVisualizer::flushBuffer();
}

void loop ()
{	
	Interface::readButtons();

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
		case LIGHT_SHOW_CIRCLE: {
			LightShow::circling();
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
			Interface::allLedsOff();
			break;
		}
		default: {
			break;
		}
	}
	FastLED.show();
}
