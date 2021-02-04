#ifndef MESSAGE_BOARD_HPP
#define MESSAGE_BOARD_HPP

#include "system/Interface.hpp"

class MessageBoard {
private:
	/* functions */

public:
	/* variables */
	static Point displayPosition;
	static CRGB colorSet[];
	static int colorIndex;

	/* functions */
	static void initColorSet (void);
	static void showMessage (void);
	static void clearBoard (void);
};

#endif
