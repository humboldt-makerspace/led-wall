#include "io/Parser.hpp"
#include "system/Interface.hpp"

int Parser::parseValue (String cmd)
{
	int begin = -1;
	int end = -1;
	for (int i = 0; i < cmd.length(); i++) {
		if (!isDigit(cmd.charAt(i))) {
			if (begin == -1) continue;
			else {
				end = i;
				break;
			}
		}
		else {
			if (begin == -1) begin = i;
			if (i == cmd.length() - 1) end = i + 1;
		}
	}
	if (begin == -1) return -1;
	return (cmd.substring(begin, end)).toInt();
}

CRGB Parser::parseColor (String cmd)
{
	int firstCom = cmd.indexOf(',');
	int secondCom = cmd.lastIndexOf(',');
	int r = parseValue(cmd);
	int g = parseValue(cmd.substring(firstCom));
	int b = parseValue(cmd.substring(secondCom));
	if (r == -1 || g == -1 || b == -1) return CRGB::Black;
	return CRGB(r, g, b);
}

WallMode Parser::parseWallMode (String cmd)
{
	if (cmd.endsWith(MODE_AUDIO)) return AUDIO_VISUALIZER;
	else if (cmd.endsWith(MODE_CLOCK_D)) return CLOCK_DIGITAL;
	else if (cmd.endsWith(MODE_CLOCK_W)) return CLOCK_WORD;
	else if (cmd.endsWith(MODE_LOOP)) return LIGHT_SHOW_LOOP;
	else if (cmd.endsWith(MODE_MATRIX)) return LIGHT_SHOW_MATRIX_VIBE;
	else if (cmd.endsWith(MODE_NETWORK)) return LIGHT_SHOW_NETWORK;
	else if (cmd.endsWith(MODE_PRIDE)) return LIGHT_SHOW_PRIDE;
	else if (cmd.endsWith(MODE_PROCESSOR)) return LIGHT_SHOW_PROCESSOR;
	else if (cmd.endsWith(MODE_STATIC)) return LIGHT_SHOW_STATIC_COLOR;
	else if (cmd.endsWith(MODE_TEST)) return TEST;
	else if (cmd.endsWith(MODE_MESSAGE)) return MESSAGE_BOARD;
	else return (WallMode)(-1);
}

ColorMode Parser::parseColorMode (String cmd)
{
	if (cmd.endsWith(COLOR_AVH_H)) return AVH_HORIZONTAL;
	else if (cmd.endsWith(COLOR_AVH_V)) return AVH_VERTICAL;
	else if (cmd.endsWith(COLOR_RAINBOW_H)) return RAINBOW_HORIZONTAL;
	else if (cmd.endsWith(COLOR_RAINBOW_V)) return RAINBOW_VERTICAL;
	else if (cmd.endsWith(COLOR_RAINBOW_SYM)) return RAINBOW_SYMMETRICAL;
	else if (cmd.endsWith(COLOR_SUPERMAN_H)) return SUPERMAN_HORIZONTAL;
	else if (cmd.endsWith(COLOR_SUPERMAN_V)) return SUPERMAN_VERTICAL;
	else if (cmd.endsWith(COLOR_TEMP_H)) return TEMPERATURE_HORIZONTAL;
	else if (cmd.endsWith(COLOR_TEMP_V)) return TEMPERATURE_VERTICAL;
	else return (ColorMode)(-1);
}
