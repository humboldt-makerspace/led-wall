#ifndef AUDIO_VISUALIZER_HPP
#define AUDIO_VISUALIZER_HPP

#include "constants.h"

class AudioVisualizer {
private:
	/* variables */
	static int bufferCounter[WALL_WIDTH];
	static float spectrumBuffer[WALL_WIDTH][BUFFER_SIZE];
	static float logBaseAudio;
	static int samplingRange;
	static int maxBarHeight;
	static int maxAmpl;
	static float bufferDec;
	static int begin[WALL_WIDTH];
	static int end[WALL_WIDTH];

	/* functions */
	static void updateBuffer(float value, int pos);
	static void flattenBuffer(int pos);
	static float getAvgValue(int pos);
	static void adjustMaxAmpl(void);

public:
	/* functions */
	static void init(void);
	static void visualizeAudio(void);
	static void flushBuffer(void);
};

#endif
