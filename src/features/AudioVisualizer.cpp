#include "features/AudioVisualizer.hpp"
#include "system/Interface.hpp"

int AudioVisualizer::bufferCounter[WALL_WIDTH];
double AudioVisualizer::spectrumBuffer[WALL_WIDTH][BUFFER_SIZE];
double AudioVisualizer::logBaseAudio = 0;
int AudioVisualizer::samplingRange = 0;

void AudioVisualizer::init (void)
{
	AudioVisualizer::samplingRange = SAMPLES / 1.2;
	AudioVisualizer::logBaseAudio = pow(WALL_WIDTH, 1.0 / (AudioVisualizer::samplingRange - 2));
}

void AudioVisualizer::flushBuffer (void)
{
	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = 0; j < BUFFER_SIZE; j++) spectrumBuffer[i][j] = 0;
		bufferCounter[i] = 0;
	}
}

void AudioVisualizer::updateBuffer (double value, int pos)
{
	spectrumBuffer[pos][bufferCounter[pos]] = value;
	if (bufferCounter[pos] == BUFFER_SIZE - 1) bufferCounter[pos] = 0;
	else bufferCounter[pos]++;
}

void AudioVisualizer::flattenBuffer (int pos)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		spectrumBuffer[pos][i] -= BUFFER_DEC;
		if (spectrumBuffer[pos][i] < 0) spectrumBuffer[pos][i] = 0;
	}
}

double AudioVisualizer::getAvgValue (int pos)
{
	double res = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) res += spectrumBuffer[pos][i];
	return res / BUFFER_SIZE;
}

void AudioVisualizer::visualizeAudio (void)
{
	AudioAnalyzer::audioFFT();

	double spectrum[WALL_WIDTH];
	for (int i = 0; i < WALL_WIDTH; i++) {
		spectrum[i] = 0.0;
		int begin = 0;
		int end = 0;
		if (i == WALL_WIDTH - 1) {
			begin = (int)(AudioVisualizer::samplingRange - 1 - Misc::logBaseX(AudioVisualizer::logBaseAudio, WALL_WIDTH - i));
			end = begin;
		}
		else {
			begin = (int)(AudioVisualizer::samplingRange - 1 - Misc::logBaseX(AudioVisualizer::logBaseAudio, WALL_WIDTH - i));
			end = (int)(AudioVisualizer::samplingRange - 1 - Misc::logBaseX(AudioVisualizer::logBaseAudio, WALL_WIDTH - i - 1));
		}
		for (int j = begin; j <= end; j++) spectrum[i] += AudioAnalyzer::vReal[j];

		if (end != begin) spectrum[i] = spectrum[i] / (end - begin);
		spectrum[i] = spectrum[i] / pow(LOW_FREQ_DAMPER, WALL_WIDTH - i);
	}
	spectrum[0] = spectrum[0] / 4.5;
	spectrum[1] = spectrum[1] / 3.0;
	spectrum[2] = spectrum[2] / 2.5;

	for (int i = 0; i < WALL_WIDTH; i++) {
		if (spectrum[i] > getAvgValue(i)) updateBuffer(spectrum[i], i);
		int barHeight = WALL_HEIGHT * (getAvgValue(i) - MIN_AMPL) / (MAX_AMPL - MIN_AMPL);
		if (barHeight < 0) barHeight = 0;
		if (barHeight > WALL_HEIGHT) barHeight = WALL_HEIGHT;
		Bars::showBar(i, barHeight);
		flattenBuffer(i);
	}
	//Interface::ledOn(WALL_WIDTH - 1, 0, ColorGradient::colors[WALL_WIDTH - 1][0]);
}
