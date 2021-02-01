#include "utils/AudioAnalyzer.hpp"
#include "system/Interface.hpp"

unsigned int AudioAnalyzer::sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
unsigned long AudioAnalyzer::microseconds;
unsigned long AudioAnalyzer::newTime, AudioAnalyzer::oldTime;
byte AudioAnalyzer::peak[] = {0,0,0,0,0,0,0};
double AudioAnalyzer::vImag[SAMPLES];
double AudioAnalyzer::vReal[SAMPLES];
arduinoFFT AudioAnalyzer::FFT = arduinoFFT(AudioAnalyzer::vReal, AudioAnalyzer::vImag, SAMPLES, SAMPLING_FREQUENCY);

void AudioAnalyzer::audioFFT (void)
{
	for (int i = 0; i < SAMPLES; i++) {
    	newTime = micros() - oldTime;
    	oldTime = newTime;
    	vReal[i] = analogRead(AUDIO_PIN) - 2900;
    	vImag[i] = 0;
    	while (micros() < (newTime + sampling_period_us));
  	}
  	FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  	FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  	FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
}
