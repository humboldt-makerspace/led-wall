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
	static void showMessage (String msg);
	static void clearBoard (void);
	static void letterShiftTest (void);
	static Format defineFormat (String msg);
};

#endif
