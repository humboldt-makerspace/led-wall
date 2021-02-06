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
	static Point displayPosition;
	static CRGB colorSet[];
	static int colorIndex;

	/* functions */
	static void initColorSet (void);
	static void showMessage (String msg, int duration);
	static void clearBoard (void);
	static void shiftMessage (String msg);
	static Format defineFormat (String msg);
	static void displayTwoWordNumbers (int num1, int num2, int height);
};

#endif
