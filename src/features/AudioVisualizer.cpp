#include "features/AudioVisualizer.hpp"
#include "system/Interface.hpp"

int AudioVisualizer::bufferCounter[WALL_WIDTH];
double AudioVisualizer::spectrumBuffer[WALL_WIDTH][BUFFER_SIZE];
double AudioVisualizer::logBaseAudio = 0;
int AudioVisualizer::samplingRange = 0;
int AudioVisualizer::maxBarHeight = 0;
int AudioVisualizer::maxAmpl;
float AudioVisualizer::bufferDec;
long adjustAmpTimer = 0;

void AudioVisualizer::init (void)
{
	AudioVisualizer::samplingRange = SAMPLES / 1.2;
	AudioVisualizer::logBaseAudio = pow(WALL_WIDTH, 1.0 / (AudioVisualizer::samplingRange - 2));
	AudioVisualizer::maxAmpl = MAX_AMPL_DEFAULT;
	AudioVisualizer::bufferDec = BUFFER_DEC_DEFAULT;
}

void AudioVisualizer::adjustMaxAmpl (void)
{
	if (millis() - adjustAmpTimer < ADJUST_AMP_TIME) return;
	adjustAmpTimer = millis();
	// if (AudioVisualizer::maxBarHeight < IGNORE_NOISE) return;
	AudioVisualizer::maxAmpl = (int)(AudioVisualizer::maxAmpl * (float)((float)AudioVisualizer::maxBarHeight / (float)WALL_HEIGHT));
	if (AudioVisualizer::maxAmpl < MIN_AMPL) AudioVisualizer::maxAmpl = MIN_AMPL + 50;
	AudioVisualizer::maxBarHeight = 0;
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
		spectrumBuffer[pos][i] -= AudioVisualizer::bufferDec;
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
	spectrum[0] = spectrum[0] / 5.0;
	spectrum[1] = spectrum[1] / 3.5;
	spectrum[2] = spectrum[2] / 3.5;

	for (int i = 0; i < WALL_WIDTH; i++) {
		if (spectrum[i] > getAvgValue(i)) updateBuffer(spectrum[i], i);
		int barHeight = WALL_HEIGHT * (getAvgValue(i) - MIN_AMPL) / (AudioVisualizer::maxAmpl - MIN_AMPL);
		if (barHeight < 0) barHeight = 0;
		if (barHeight > AudioVisualizer::maxBarHeight) AudioVisualizer::maxBarHeight = barHeight;
		// if (barHeight > WALL_HEIGHT - 1) barHeight = WALL_HEIGHT - 1;
		Bars::showBar(i, barHeight);
		flattenBuffer(i);
	}
	AudioVisualizer::adjustMaxAmpl();
	//Interface::ledOn(WALL_WIDTH - 1, 0, ColorGradient::colors[WALL_WIDTH - 1][0]);
	// Serial.print("AUDIO SIGNAL: ");
	// Serial.println(spectrum[1]);
}
