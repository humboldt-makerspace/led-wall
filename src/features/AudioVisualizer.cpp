#include "features/AudioVisualizer.hpp"
#include "system/Interface.hpp"

int AudioVisualizer::bufferCounter[WALL_WIDTH];
float AudioVisualizer::spectrumBuffer[WALL_WIDTH][BUFFER_SIZE];
float AudioVisualizer::logBaseAudio = 0;
int AudioVisualizer::samplingRange = 0;
int AudioVisualizer::maxBarHeight = 0;
int AudioVisualizer::maxAmpl;
float AudioVisualizer::bufferDec;
int AudioVisualizer::begin[WALL_WIDTH];
int AudioVisualizer::end[WALL_WIDTH];
long adjustAmpTimer = 0;

void AudioVisualizer::init(void)
{
	samplingRange = SAMPLES / 1.2;
	logBaseAudio = pow(WALL_WIDTH, 1.0 / (samplingRange - 2));
	maxAmpl = MAX_AMPL_DEFAULT;
	bufferDec = BUFFER_DEC_DEFAULT;

	for (int i = 0; i < WALL_WIDTH; i++) {
		if (i == WALL_WIDTH - 1) {
			begin[i] = (int)(samplingRange - 1 - Misc::logBaseX(logBaseAudio, WALL_WIDTH - i));
			end[i] = begin[i];
		}
		else {
			begin[i] = (int)(samplingRange - 1 - Misc::logBaseX(logBaseAudio, WALL_WIDTH - i));
			end[i] = (int)(samplingRange - 1 - Misc::logBaseX(logBaseAudio, WALL_WIDTH - i - 1));
		}
	}
}

void AudioVisualizer::adjustMaxAmpl(void)
{
	if (millis() - adjustAmpTimer < ADJUST_AMP_TIME) return;
	adjustAmpTimer = millis();
	// if (maxBarHeight < IGNORE_NOISE) return;
	maxAmpl = (int)(maxAmpl * (float)((float)maxBarHeight / (float)WALL_HEIGHT));
	if (maxAmpl < MIN_AMPL) maxAmpl = MIN_AMPL + 50;
	maxBarHeight = 0;
	bufferDec = maxAmpl / DEC_DIV;
}

void AudioVisualizer::flushBuffer(void)
{
	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = 0; j < BUFFER_SIZE; j++) spectrumBuffer[i][j] = 0;
		bufferCounter[i] = 0;
	}
}

void AudioVisualizer::updateBuffer(float value, int pos)
{
	spectrumBuffer[pos][bufferCounter[pos]] = value;
	if (bufferCounter[pos] == BUFFER_SIZE - 1) bufferCounter[pos] = 0;
	else bufferCounter[pos]++;
}

void AudioVisualizer::flattenBuffer(int pos)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		spectrumBuffer[pos][i] -= bufferDec;
		if (spectrumBuffer[pos][i] < 0) spectrumBuffer[pos][i] = 0;
	}
}

float AudioVisualizer::getAvgValue(int pos)
{
	float res = 0;
	for (int i = 0; i < BUFFER_SIZE; i++) res += spectrumBuffer[pos][i];
	return res / BUFFER_SIZE;
}

void AudioVisualizer::visualizeAudio(void)
{
#ifndef USE_DUAL_CORE
	AudioAnalyzer::audioFFT();
#else
	if (!AudioAnalyzer::newDataAvailable) return;
	AudioAnalyzer::newDataAvailable = false;
#endif

	float spectrum[WALL_WIDTH];
	for (int i = 0; i < WALL_WIDTH; i++) {
		spectrum[i] = 0.0;
		for (int j = begin[i]; j <= end[i]; j++) spectrum[i] += AudioAnalyzer::vReal[j];
		spectrum[i] = spectrum[i] / ((end[i] - begin[i] + 1) * pow(LOW_FREQ_DAMPER, WALL_WIDTH - i));
		if (i == 0) spectrum[0] = spectrum[0] / 5.0;
		else if (i == 1) spectrum[1] = spectrum[1] / 3.5;
		else if (i == 2) spectrum[2] = spectrum[2] / 3.5;

		if (spectrum[i] > getAvgValue(i)) updateBuffer(spectrum[i], i);
		int barHeight = WALL_HEIGHT * (getAvgValue(i) - MIN_AMPL) / (maxAmpl - MIN_AMPL);
		if (barHeight < 0) barHeight = 0;
		if (barHeight > maxBarHeight) maxBarHeight = barHeight;
		// if (barHeight > WALL_HEIGHT - 1) barHeight = WALL_HEIGHT - 1;
		Bars::showBar(i, barHeight);
		flattenBuffer(i);
	}

	adjustMaxAmpl();
	//Interface::ledOn(WALL_WIDTH - 1, 0, ColorGradient::colors[WALL_WIDTH - 1][0]);
	// Serial.print("AUDIO SIGNAL: ");
	// Serial.println(spectrum[1]);
}
