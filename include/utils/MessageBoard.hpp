#ifndef MESSAGE_BOARD_HPP
#define MESSAGE_BOARD_HPP

#include "system/Interface.hpp"
#include "CustomTypes.h"

class MessageBoard {
private:
	/* variables */
	static unsigned long time;

	/* functions */

public:
	/* variables */
	static point_t displayPosition;
	static CRGB colorSet[];
	static int colorIndex;

	/* functions */
	static void initColorSet(void);
	static void showMessage(String const &msg, int duration);
	static void clearBoard(void);
	static void shiftMessage(String const &msg);
	static msg_format_t defineFormat(String const &msg);
	static void displayTwoWordNumbers(int num1, int num2, int height);
};

#endif
