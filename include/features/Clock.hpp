#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ctime>

class Clock {
private:
	/* functions */
	static void getTime (void);

public:
	/* variables */
	static tm* gmtm;

	/* functions */
	static void showTimeDigits (void);
	static void showTimeWords (void);
};

#endif
