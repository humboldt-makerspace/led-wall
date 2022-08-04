#ifndef CONSTANTS_H
#define CONSTANTS_H

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
#define SAMPLES					128
#define SAMPLING_FREQUENCY		36000
#define MIN_AMPL				10
#define MAX_AMPL_DEFAULT		800
#define BUFFER_SIZE				3
#define DEC_DIV					8
#define LOW_FREQ_DAMPER			1.03 //1.043 			//1.045 forward
#define BUFFER_DEC_DEFAULT		MAX_AMPL_DEFAULT / DEC_DIV
#define ADJUST_AMP_TIME			10000
#define IGNORE_NOISE			3

/* parameters to change color and brightness */
#define COLOR_INC				40
#define BRIGHTNESS_DEC			20

/* parameters for figures */
#define NUM_FIGURES				39
#define NUM_BIG_NUM				10
#define BIG_NUM_WIDTH			7
#define BIG_NUM_HEIGHT			16
#define FIGURE_WIDTH			5
#define FIGURE_HEIGHT			7
#define MSG_COL_NUM				7
#define FIRST_ROW_LEVEL			10
#define MIDDLE_ROW_LEVEL		6
#define BOARD_FADEOUT_TIME		1000
#define MSG_DURATION			4000
#define QUICK_NOTE_DURATION		1000
#define WORD_SPACING			2

/* parameters for clock */
#define HR_1_POS				0
#define HR_2_POS				8
#define MIN_1_POS				20
#define MIN_2_POS				28
#define SEC_1_POS				40
#define SEC_2_POS				48
#define NUMBER_LEVEL			1
#define COLON_1_POS				17
#define COLON_2_POS				37
#define COLON_HEIGHT			7
#define TIME_ZONE				1
#define DST						1

/* fade factors, higher value means faster fading */
#define FADE_FACTOR_OFF			50
#define FADE_FACTOR_CLOCK		60
#define FADE_FACTOR_BARS		150
#define FADE_FACTOR_DOTS		100
#define FADE_FACTOR_FIGURE		50

/* moving dots */
#define MAX_NUM_DOTS_MATRIX		30
#define MAX_NUM_DOTS_PROCESSOR	60
#define MAX_NUM_DOTS_CIRCLE		8
#define MAX_NUM_DOTS_NETWORK	60
#define MAX_NUM_DOTS			100
#define WEAKEN_FACTOR			0.00
#define LAST_FIELDS_NUM			12
#define PROCESSOR_SIZE			8

/* WiFi and UDP */
#define MAX_PACKET_SIZE			100

/* command prefixes */
#define CMD_MODE				"/mode"
#define CMD_BRIGHTNESS			"/brightness"
#define CMD_COLOR				"/color"

/* command suffixes */
#define MODE_PRIDE				"pride"
#define MODE_STATIC				"static"
#define MODE_MATRIX				"matrix"
#define MODE_PROCESSOR			"processor"
#define MODE_LOOP				"loop"
#define MODE_NETWORK			"network"
#define MODE_CLOCK_D			"clockd"
#define MODE_CLOCK_W			"clockw"
#define MODE_TEST				"test"
#define MODE_AUDIO				"audio"
#define MODE_MESSAGE			"message"

#define COLOR_RAINBOW_H			"rainbowh"
#define COLOR_RAINBOW_V			"rainbowv"
#define COLOR_RAINBOW_SYM		"rainbows"
#define COLOR_SUPERMAN_H		"supermanh"
#define COLOR_SUPERMAN_V		"supermanv"
#define COLOR_AVH_H				"avhh"
#define COLOR_AVH_V				"avhv"
#define COLOR_TEMP_H			"temperatureh"
#define COLOR_TEMP_V			"temperaturev"

/* lists all features of led wall */
typedef enum modeTypes {
	LIGHT_SHOW_PRIDE,
	LIGHT_SHOW_STATIC_COLOR,
	LIGHT_SHOW_MATRIX_VIBE,
	LIGHT_SHOW_PROCESSOR,
	LIGHT_SHOW_LOOP,
	LIGHT_SHOW_NETWORK,
	CLOCK_DIGITAL,
	CLOCK_WORD,
	MESSAGE_BOARD,
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
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, EXC, QUEST, SPACE
} Figure;

typedef enum bigNumbers {
	Z0, Z1, Z2, Z3, Z4, Z5, Z6, Z7, Z8, Z9
} BigNumber;

/* directions for moving a dot */
typedef enum directions {
	UP, DOWN, LEFT, RIGHT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT
} Direction;

#endif
