#include "utils/AudioAnalyzer.hpp"
#include "system/Interface.hpp"

unsigned int AudioAnalyzer::samplingPeriodUs = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
unsigned long AudioAnalyzer::microseconds;
unsigned long AudioAnalyzer::newTime, AudioAnalyzer::oldTime;
byte AudioAnalyzer::peak[] = {0, 0, 0, 0, 0, 0, 0};
float AudioAnalyzer::vImag[SAMPLES];
float AudioAnalyzer::vReal[SAMPLES];
arduinoFFT AudioAnalyzer::FFT = arduinoFFT(AudioAnalyzer::vReal, AudioAnalyzer::vImag, SAMPLES, SAMPLING_FREQUENCY);
TaskHandle_t xTaskFFTHandler;
bool AudioAnalyzer::newDataAvailable = false;

// never use sample 0
void AudioAnalyzer::audioFFT(void)
{
	for (int i = 0; i < SAMPLES; i++) {
		newTime = micros() - oldTime;
		oldTime = newTime;
		vReal[i] = analogRead(AUDIO_PIN) - 2900;
		vImag[i] = 0;
		while (micros() - newTime < samplingPeriodUs);
	}
	FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
	FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
	FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
#ifdef USE_DUAL_CORE
	newDataAvailable = true;
#endif
}

void AudioAnalyzer::fft_task(void *parameter)
{
	for (;;) {
		audioFFT();
		vTaskDelay(1);
	}
}

void AudioAnalyzer::fft_task_init(uint32_t ulStackDepth, UBaseType_t uxPriority, const BaseType_t xCoreID)
{
	xTaskCreatePinnedToCore(
		fft_task,
		"fft_task",
		ulStackDepth,
		(void *)1,
		uxPriority,
		&xTaskFFTHandler,
		xCoreID);
}
