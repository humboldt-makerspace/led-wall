#ifndef AUDIO_ANALYZER_HPP
#define AUDIO_ANALYZER_HPP

#include "system/Interface.hpp"

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

	/* functions */
	static void audioFFT(void);
};

#endif
