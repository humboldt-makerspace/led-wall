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
	MessageBoard::colorSet[1] = CRGB(255, 134, 51);
	MessageBoard::colorSet[2] = CRGB::Yellow;
	MessageBoard::colorSet[3] = CRGB::Green;
	MessageBoard::colorSet[4] = CRGB::Cyan;
	MessageBoard::colorSet[5] = CRGB::Blue;
	MessageBoard::colorSet[6] = CRGB::Violet;
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
		isWhitespace(msg.charAt(i)) ? rowWidth += WORD_SPACING : rowWidth += FIGURE_WIDTH;
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
		isWhitespace(msg.charAt(i)) ? rowWidth += WORD_SPACING : rowWidth += FIGURE_WIDTH;
		if (rowWidth > WALL_WIDTH - 1) {
			f.endInd2 = i - 1;
			break;
		}
		lastRowWidth = rowWidth;
	}
	f.pos2 = (WALL_WIDTH - lastRowWidth) / 2;
	return f;
}

void MessageBoard::showMessage (String msg, int duration)
{
	if (msg.isEmpty()) return;
	else if (msg.charAt(0) == '/') return;
	MessageBoard::clearBoard();
	Format f = defineFormat(msg);
	MessageBoard::time = millis();
	int finalIndex1 = -1;
	int finalIndex2 = -1;

	while (millis() - MessageBoard::time < duration) {
		finalIndex1 = msg.length();
		if (f.endInd1 != -1) {
			finalIndex1 = f.endInd1;
			MessageBoard::displayPosition.y = FIRST_ROW_LEVEL;
		}
		else MessageBoard::displayPosition.y = MIDDLE_ROW_LEVEL;
		MessageBoard::displayPosition.x = f.pos1;
		MessageBoard::colorIndex = 0;

		for (int i = 0; i < finalIndex1; i++) {
			if (isWhitespace(msg.charAt(i))) MessageBoard::displayPosition.x += WORD_SPACING;
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
			if (isWhitespace(msg.charAt(i))) MessageBoard::displayPosition.x += WORD_SPACING;
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
	if (finalIndex2 != msg.length()) MessageBoard::showMessage(msg.substring(finalIndex2), duration);
}

void MessageBoard::shiftMessage (String msg)
{
	if (msg.isEmpty()) return;
	MessageBoard::clearBoard();
	int height = rand() % (WALL_HEIGHT - FIGURE_HEIGHT + 1);
	int endPoint = 1;
	MessageBoard::displayPosition.x = WALL_WIDTH;
	while (endPoint > -FIGURE_WIDTH) {
		MessageBoard::colorIndex = 0;
		for (int i = 0; i < msg.length(); i++) {
			Figures::displayFigureHard(Figures::charToFigure(msg.charAt(i)),
							   MessageBoard::displayPosition.x + FIGURE_WIDTH * i,
							   height,
							   MessageBoard::colorSet[colorIndex]);
			MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
			endPoint = MessageBoard::displayPosition.x + FIGURE_WIDTH * i;
		}
		Figures::displayFigureHard(SPACE,
							   	   endPoint + FIGURE_WIDTH,
							   	   height,
							   	   MessageBoard::colorSet[colorIndex]);
		MessageBoard::displayPosition.x--;
		FastLED.show();
		//delay(100);
	}  
}

void MessageBoard::displayTwoWordNumbers (int num1, int num2, int height)
{
	String first = Misc::numToWord(num1);
	String second = Misc::numToWord(num2);

	for (int i = 0; i < WALL_WIDTH; i++) {
		for (int j = height; j < height + FIGURE_HEIGHT; j++) {
			Interface::fadeToColor(i, j, CRGB::Black, FADE_FACTOR_CLOCK);
		}
	}

	MessageBoard::displayPosition.x = 0;
	MessageBoard::displayPosition.y = height;
	MessageBoard::colorIndex = 0;

	for (int i = 0; i < first.length(); i++) {
		Figures::displayFigure(Figures::charToFigure(first.charAt(i)),
							   MessageBoard::displayPosition.x + FIGURE_WIDTH * i,
							   height,
							   MessageBoard::colorSet[colorIndex]);
		MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
	}

	MessageBoard::displayPosition.x = WALL_WIDTH - FIGURE_WIDTH * second.length();
	for (int i = 0; i < second.length(); i++) {
		Figures::displayFigure(Figures::charToFigure(second.charAt(i)),
							   MessageBoard::displayPosition.x + FIGURE_WIDTH * i,
							   height,
							   MessageBoard::colorSet[colorIndex]);
		MessageBoard::colorIndex == MSG_COL_NUM - 1 ? MessageBoard::colorIndex = 0 : MessageBoard::colorIndex++;
	}
}
