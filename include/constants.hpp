#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/* data pins for led stripes */
#define LED_PIN_1               25
#define LED_PIN_2               26
#define LED_PIN_3               27

/* number of leds per data pin */
#define NUM_LEDS				336

/* number of data pins */
#define NUM_DATA_PINS			3

/* red status led pin on control pcb */
#define STATUS_LED_PIN          33

/* buttons on control pcb */
#define BUTTON_1_PIN            14
#define BUTTON_2_PIN            16
#define BUTTON_3_PIN            17
#define NUM_BUTTONS             3

/* dimensions of led wall in leds */
#define WALL_HEIGHT				18
#define WALL_WIDTH				56

/* pin for audio input */
#define AUDIO_PIN				35

/* values for FFT */
#define SAMPLES					1024
#define SAMPLING_RANGE			256
#define SAMPLING_FREQUENCY		36000
#define MIN_AMPL				10
#define MAX_AMPL				800
#define BUFFER_SIZE				3
#define LOG_BASE				1.0160377266	//1.007939707 with 512 //pow(WALL_WIDTH, 1 / (SAMPLING_RANGE - 2))
#define LOW_FREQ_DAMPER			1.043 			//1.045 forward
#define BUFFER_DEC				MAX_AMPL / 5

/* parameters to change color and brightness */
#define COLOR_INC				40
#define BRIGHTNESS_DEC			20

/* parameters for figures */
#define NUM_FIGURES				36
#define FIGURE_WIDTH			7
#define FIGURE_HEIGHT			16

/* parameters for clock */
#define HR_1_POS				0
#define HR_2_POS				8
#define MIN_1_POS				20
#define MIN_2_POS				28
#define SEC_1_POS				40
#define SEC_2_POS				48
#define NUMBER_HEIGHT			1
#define COLON_1_POS				17
#define COLON_2_POS				37
#define COLON_HEIGHT			7
#define TIME_ZONE				1
#define DST						1

/* fade factors, higher value means faster fading */
#define FADE_FACTOR_OFF			100
#define FADE_FACTOR_CLOCK		60
#define FADE_FACTOR_BARS		150
#define FADE_FACTOR_DOTS		100

/* moving dots */
#define MAX_NUM_DOTS_MATRIX		30
#define MAX_NUM_DOTS_PROCESSOR	60
#define MAX_NUM_DOTS_CIRCLE		8
#define MAX_NUM_DOTS_NETWORK	60
#define MAX_NUM_DOTS			100
#define WEAKEN_FACTOR			0.00
#define LAST_FIELDS_NUM			12
#define PROCESSOR_SIZE			8

/* lists all features of led wall */
typedef enum modeTypes {
	LIGHT_SHOW_PRIDE,
	LIGHT_SHOW_STATIC_COLOR,
	LIGHT_SHOW_MATRIX_VIBE,
	LIGHT_SHOW_PROCESSOR,
	LIGHT_SHOW_CIRCLE,
	LIGHT_SHOW_NETWORK,
	CLOCK,
	TEST,
	AUDIO_VISUALIZER
} WallMode;

/* color modes for bar visualization */
typedef enum colors {
	RAINBOW_HORIZONTAL,
	RAINBOW_VERTICAL,
	RAINBOW_SYMMETRICAL,
	SUPERMAN_HORIZONTAL,
	SUPERMAN_VERTICAL,
	AVH_HORIZONTAL,
	AVH_VERTICAL,
	TEMPERATURE_HORIZONTAL,
	TEMPERATURE_VERTICAL,
	MONO
} ColorMode;

/* all figures that be displayed on led wall */
typedef enum figures {
	N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
} Figure;

/* directions for moving a dot */
typedef enum directions {
	UP, DOWN, LEFT, RIGHT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT
} Direction;

#endif
