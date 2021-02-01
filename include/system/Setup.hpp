#ifndef SETUP_HPP
#define SETUP_HPP

#include "WiFiUdp.h"

class Setup {
private:
	/* variables */
	static WiFiUDP UDPServer;

	/* functions */
	static void initWifi (void);

public:
	/* variables */

	/* functions */
	static void init (void);
};

#endif
