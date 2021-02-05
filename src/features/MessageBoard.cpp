#include "features/MessageBoard.hpp"
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

void MessageBoard::showMessage (String msg)
{
	if (msg.isEmpty()) return;
	else if (msg.charAt(0) == '/') return;
	MessageBoard::clearBoard();
	for (int i = 0; i < msg.length(); i++) {
		Figures::displayFigureMono(Figures::charToFigure(msg.charAt(i)),
								   MessageBoard::displayPosition.x,
								   MessageBoard::displayPosition.y,
								   MessageBoard::colorSet[colorIndex]);
		MessageBoard::displayPosition.x += FIGURE_WIDTH;
		if (MessageBoard::displayPosition.x > WALL_WIDTH - FIGURE_WIDTH) {
			if (MessageBoard::displayPosition.y == FIRST_ROW_LEVEL) {
				MessageBoard::displayPosition.x = 0;
				MessageBoard::displayPosition.y = 0;
			}
			else {
				FastLED.show();
				delay(DISPLAY_TIME);
				MessageBoard::clearBoard();
			}
		}
		MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
	}
}

void MessageBoard::letterShiftTest (void)
{
	Figures::displayFigureMono(D,
							   MessageBoard::displayPosition.x,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[3]);
	Figures::displayFigureMono(U,
							   MessageBoard::displayPosition.x + FIGURE_WIDTH,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[4]);
	Figures::displayFigureMono(C,
							   MessageBoard::displayPosition.x + 2 * FIGURE_WIDTH,
							   MessageBoard::displayPosition.y,
							   MessageBoard::colorSet[5]);
	MessageBoard::displayPosition.x >= 40 ? MessageBoard::displayPosition.x = 0 : MessageBoard::displayPosition.x++;				   
}
