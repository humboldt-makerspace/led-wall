#include "utils/MessageBoard.hpp"
#include "system/Interface.hpp"

unsigned long MessageBoard::time = 0;
Point MessageBoard::displayPosition = {
	.x = 0,
	.y = FIRST_ROW_LEVEL
};
CRGB MessageBoard::colorSet[MSG_COL_NUM];
int MessageBoard::colorIndex = 0;

void MessageBoard::initColorSet (void)
{
	MessageBoard::colorSet[0] = CRGB::Red;
	MessageBoard::colorSet[1] = CRGB::Orange;
	MessageBoard::colorSet[2] = CRGB::Yellow;
	MessageBoard::colorSet[3] = CRGB::YellowGreen;
	MessageBoard::colorSet[4] = CRGB::Green;
	MessageBoard::colorSet[5] = CRGB::Cyan;
	MessageBoard::colorSet[6] = CRGB::Blue;
	MessageBoard::colorSet[7] = CRGB::Violet;
}

void MessageBoard::clearBoard (void)
{
	MessageBoard::time = millis();
	MessageBoard::displayPosition.x = 0;
	MessageBoard::displayPosition.y = FIRST_ROW_LEVEL;
	MessageBoard::colorIndex = 0;
	while (millis() - MessageBoard::time < BOARD_FADEOUT_TIME) {
		Interface::fadeOutAll(FADE_FACTOR_OFF);
		FastLED.show();
	}
}

Format MessageBoard::defineFormat (String msg)
{
	Format f = {
		.endInd1 = -1,
		.endInd2 = -1,
		.pos1 = -1,
		.pos2 = -1
	};

	int rowWidth = 0;
	int lastRowWidth = 0;
	for (int i = 0; i < msg.length(); i++) {
		isWhitespace(msg.charAt(i)) ? rowWidth++ : rowWidth += FIGURE_WIDTH;
		if (rowWidth > WALL_WIDTH - 1) {
			f.endInd1 = i;
			break;
		}
		lastRowWidth = rowWidth;
	}
	f.pos1 = (WALL_WIDTH - lastRowWidth) / 2;
	if (f.endInd1 == -1) return f;

	rowWidth = 0;
	lastRowWidth = 0;
	for (int i = f.endInd1; i < msg.length(); i++) {
		isWhitespace(msg.charAt(i)) ? rowWidth++ : rowWidth += FIGURE_WIDTH;
		if (rowWidth > WALL_WIDTH - 1) {
			f.endInd2 = i - 1;
			break;
		}
		lastRowWidth = rowWidth;
	}
	f.pos2 = (WALL_WIDTH - lastRowWidth) / 2;
	return f;
}

void MessageBoard::showMessage (String msg)
{
	if (msg.isEmpty()) return;
	else if (msg.charAt(0) == '/') return;
	MessageBoard::clearBoard();
	Format f = defineFormat(msg);
	MessageBoard::time = millis();
	int finalIndex1 = -1;
	int finalIndex2 = -1;

	while (millis() - time < DISPLAY_TIME) {
		finalIndex1 = msg.length();
		if (f.endInd1 != -1) finalIndex1 = f.endInd1;
		else MessageBoard::displayPosition.y = MIDDLE_ROW_LEVEL;
		MessageBoard::displayPosition.x = f.pos1;
		MessageBoard::colorIndex = 0;

		for (int i = 0; i < finalIndex1; i++) {
			if (isWhitespace(msg.charAt(i))) MessageBoard::displayPosition.x++;
			else {
				Figures::displayFigure(Figures::charToFigure(msg.charAt(i)),
									   MessageBoard::displayPosition.x,
									   MessageBoard::displayPosition.y,
									   MessageBoard::colorSet[colorIndex]);
				MessageBoard::displayPosition.x += FIGURE_WIDTH;
				MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
			}
		}

		finalIndex2 = msg.length();
		if (f.endInd2 != -1) finalIndex2 = f.endInd2;
		MessageBoard::displayPosition.y = 0;
		MessageBoard::displayPosition.x = f.pos2;
		for (int i = finalIndex1; i < finalIndex2; i++) {
			if (isWhitespace(msg.charAt(i))) MessageBoard::displayPosition.x++;
			else {
				Figures::displayFigure(Figures::charToFigure(msg.charAt(i)),
									   MessageBoard::displayPosition.x,
									   MessageBoard::displayPosition.y,
									   MessageBoard::colorSet[colorIndex]);
				MessageBoard::displayPosition.x += FIGURE_WIDTH;
				MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
			}
		}
		FastLED.show();
	}
	MessageBoard::clearBoard();
	if (finalIndex2 != msg.length()) MessageBoard::showMessage(msg.substring(finalIndex2));
}

void MessageBoard::letterShiftTest (void)
{
	Figures::displayFigure(D,
							   MessageBoard::displayPosition.x,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[3]);
	Figures::displayFigure(U,
							   MessageBoard::displayPosition.x + FIGURE_WIDTH,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[4]);
	Figures::displayFigure(C,
							   MessageBoard::displayPosition.x + 2 * FIGURE_WIDTH,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[5]);
	MessageBoard::displayPosition.x >= 40 ? MessageBoard::displayPosition.x = 0 : MessageBoard::displayPosition.x++;				   
}
