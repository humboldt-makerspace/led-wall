#ifndef PARSER_HPP
#define PARSER_HPP

#include "system/Interface.hpp"

class Parser {
private:
	/* functions */

public:
	/* variables */

	/* functions */
	static int parseValue (String cmd);
	static CRGB parseColor (String cmd);
	static WallMode parseWallMode (String cmd);
	static ColorMode parseColorMode (String cmd);
};

#endif
