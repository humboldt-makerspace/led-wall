#ifndef AUDIO_ANALYZER_HPP
#define AUDIO_ANALYZER_HPP

#include "system/Interface.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AudioAnalyzer {
private:
	/* variables */
	static unsigned int samplingPeriodUs;
	static unsigned long microseconds;
	static unsigned long newTime, oldTime;
	static byte peak[];
	static float vImag[SAMPLES];
	static arduinoFFT FFT;

public:
	/* variables */
	static float vReal[SAMPLES];
	static bool newDataAvailable;

	/* functions */
	static void audioFFT(void);
	static void fft_task(void *parameter);
	static void fft_task_init(uint32_t ulStackDepth = 4096, UBaseType_t uxPriority = 2, const BaseType_t xCoreID = 0);
};

#endif
