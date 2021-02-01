#ifndef AUDIO_VISUALIZER_HPP
#define AUDIO_VISUALIZER_HPP

#include "constants.hpp"

class AudioVisualizer {
private:
	/* variables */
	static int bufferCounter[WALL_WIDTH];
	static double spectrumBuffer[WALL_WIDTH][BUFFER_SIZE];

	/* functions */
	static void updateBuffer (double value, int pos);
	static void flattenBuffer (int pos);
	static double getAvgValue (int pos);

public:
	/* functions */
	static void visualizeAudio (void);
	static void flushBuffer (void);
};

#endif
