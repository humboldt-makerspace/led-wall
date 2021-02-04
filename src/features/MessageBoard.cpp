#include "features/MessageBoard.hpp"
#include "system/Interface.hpp"

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
	Interface::fadeOutAll(FADE_FACTOR_OFF);
	MessageBoard::displayPosition.x = 0;
	MessageBoard::displayPosition.y = FIRST_ROW_LEVEL;
	MessageBoard::colorIndex = 0;
	delay(500);
}

void MessageBoard::showMessage (void)
{
	String inc = UDPManager::readPackage();
	if (inc.isEmpty()) return;
	MessageBoard::clearBoard();
	for (int i = 0; i < inc.length(); i++) {
		Figures::displayFigureMono(Figures::charToFigure(inc.charAt(i)),
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
