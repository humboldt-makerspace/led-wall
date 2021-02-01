#include "utils/ColorGradient.hpp"
#include "system/Interface.hpp"

CRGB ColorGradient::colorsHorizontal[WALL_WIDTH];
CRGB ColorGradient::colorsVertical[WALL_HEIGHT];
CRGB ColorGradient::colors[WALL_WIDTH][WALL_HEIGHT];

void fillGradientRGB(CRGB* input, uint16_t startpos, CRGB startcolor, uint16_t endpos, CRGB endcolor)
{
    if (endpos < startpos) {
        uint16_t t = endpos;
        CRGB tc = endcolor;
        endcolor = startcolor;
        endpos = startpos;
        startpos = t;
        startcolor = tc;
    }

    saccum87 rdistance87;
    saccum87 gdistance87;
    saccum87 bdistance87;

    rdistance87 = (endcolor.r - startcolor.r) << 7;
    gdistance87 = (endcolor.g - startcolor.g) << 7;
    bdistance87 = (endcolor.b - startcolor.b) << 7;

    uint16_t pixeldistance = endpos - startpos;
    int16_t divisor = pixeldistance ? pixeldistance : 1;

    saccum87 rdelta87 = rdistance87 / divisor;
    saccum87 gdelta87 = gdistance87 / divisor;
    saccum87 bdelta87 = bdistance87 / divisor;

    rdelta87 *= 2;
    gdelta87 *= 2;
    bdelta87 *= 2;

    accum88 r88 = startcolor.r << 8;
    accum88 g88 = startcolor.g << 8;
    accum88 b88 = startcolor.b << 8;
    for (uint16_t i = startpos; i <= endpos; i++) {
        input[i] = CRGB( r88 >> 8, g88 >> 8, b88 >> 8);
        r88 += rdelta87;
        g88 += gdelta87;
        b88 += bdelta87;
    }
}

void ColorGradient::fillCompleteWall (ColorMode mode)
{
	switch (mode) {
		case RAINBOW_HORIZONTAL:
		case RAINBOW_SYMMETRICAL:
		case SUPERMAN_HORIZONTAL:
		case AVH_HORIZONTAL:
		case TEMPERATURE_HORIZONTAL:
			for (int i = 0; i < WALL_WIDTH; i++) {
				for (int j = 0; j < WALL_HEIGHT; j++) {
					colors[i][j] = colorsHorizontal[i];
				}
			}
			break;
		case RAINBOW_VERTICAL:
		case SUPERMAN_VERTICAL:
		case AVH_VERTICAL:
		case TEMPERATURE_VERTICAL:
			for (int i = 0; i < WALL_WIDTH; i++) {
				for (int j = 0; j < WALL_HEIGHT; j++) {
					colors[i][j] = colorsVertical[j];
				}
			}
			break;
		case MONO:
			for (int i = 0; i < WALL_WIDTH; i++) {
				for (int j = 0; j < WALL_HEIGHT; j++) {
					colors[i][j] = Interface::getColor();
				}
			}
		default:
			break;
	}
}

void ColorGradient::changeColorGradient (ColorMode mode)
{
	CRGB avhGreen = CRGB(211, 178, 139);
	CRGB avhBlue = CRGB(203, 128, 219);
	CRGB avhOrange = CRGB(182, 244, 112);

	switch (mode) {
		case RAINBOW_HORIZONTAL:
			fillGradientRGB(colorsHorizontal, 0, CRGB::Green, (WALL_WIDTH - 1) / 3, CRGB::Red);
			fillGradientRGB(colorsHorizontal, (WALL_WIDTH - 1) / 3, CRGB::Red, 2 * (WALL_WIDTH - 1) / 3, CRGB::Blue);
			fillGradientRGB(colorsHorizontal, 2 * (WALL_WIDTH - 1) / 3, CRGB::Blue, WALL_WIDTH - 1, CRGB::Green);
			break;
		case RAINBOW_VERTICAL:
			fillGradientRGB(colorsVertical, 0, CRGB::Green, (WALL_HEIGHT - 1) / 3, CRGB::Red);
			fillGradientRGB(colorsVertical, (WALL_HEIGHT - 1) / 3, CRGB::Red, 2 * (WALL_HEIGHT - 1) / 3, CRGB::Blue);
			fillGradientRGB(colorsVertical, 2 * (WALL_HEIGHT - 1) / 3, CRGB::Blue, WALL_HEIGHT - 1, CRGB::Green);
			break;
		case RAINBOW_SYMMETRICAL:
			fillGradientRGB(colorsHorizontal, 0, CRGB::Green, (WALL_WIDTH - 1) / 6, CRGB::Blue);
			fillGradientRGB(colorsHorizontal, (WALL_WIDTH - 1) / 6, CRGB::Blue, 2 * (WALL_WIDTH - 1) / 6, CRGB::Red);
			fillGradientRGB(colorsHorizontal, 2 * (WALL_WIDTH - 1) / 6, CRGB::Red, 3 * (WALL_WIDTH - 1) / 6, CRGB::Green);
			fillGradientRGB(colorsHorizontal, 3 * (WALL_WIDTH - 1) / 6 + 1, CRGB::Green, 4 * (WALL_WIDTH - 1) / 6, CRGB::Red);
			fillGradientRGB(colorsHorizontal, 4 * (WALL_WIDTH - 1) / 6, CRGB::Red, 5 * (WALL_WIDTH - 1) / 6, CRGB::Blue);
			fillGradientRGB(colorsHorizontal, 5 * (WALL_WIDTH - 1) / 6, CRGB::Blue, WALL_WIDTH - 1, CRGB::Green);
			break;
		case SUPERMAN_HORIZONTAL:
			fillGradientRGB(colorsHorizontal, 0, CRGB::Green, WALL_WIDTH - 1, CRGB::Blue);
			break;
		case SUPERMAN_VERTICAL:
			fillGradientRGB(colorsVertical, 0, CRGB::Green, WALL_HEIGHT - 1, CRGB::Blue);
			break;
		case AVH_HORIZONTAL:
			fillGradientRGB(colorsHorizontal, 0, avhGreen, WALL_WIDTH / 2, avhBlue);
			fillGradientRGB(colorsHorizontal, WALL_WIDTH / 2, avhBlue, WALL_WIDTH - 1, avhOrange);
			break;
		case AVH_VERTICAL:
			fillGradientRGB(colorsVertical, 0, CRGB(211, 178, 139), WALL_HEIGHT / 2, CRGB(203, 128, 219));
			fillGradientRGB(colorsVertical, WALL_HEIGHT / 2, CRGB(203, 128, 219), WALL_HEIGHT - 1, CRGB(182, 244, 112));
			break;
		case TEMPERATURE_HORIZONTAL:
			fillGradientRGB(colorsHorizontal, 0, CRGB::Green, WALL_WIDTH - 1, CRGB::Red);
			break;
		case TEMPERATURE_VERTICAL:
			fillGradientRGB(colorsVertical, 0, CRGB::Green, WALL_HEIGHT - 1, CRGB::Red);
			break;
		default:
			break;
	}
	fillCompleteWall(mode);
}
