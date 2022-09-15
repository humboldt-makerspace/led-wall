#ifndef PARSER_HPP
#define PARSER_HPP

#include "system/Interface.hpp"

class Parser {
private:
	/* functions */

public:
	/* variables */

	/* functions */
	static int parseValue(String const &cmd);
	static CRGB parseColor(String const &cmd);
	static wall_mode_t parseWallMode(String const &cmd);
	static color_mode_t parseColorMode(String const &cmd);
};

#endif
