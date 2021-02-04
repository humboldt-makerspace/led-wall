#ifndef UDP_MANAGER_HPP
#define UDP_MANAGER_HPP

#include "constants.hpp"
#include "WiFiUdp.h"

class UDPManager {
private:

public:
	/* variables */
	static WiFiUDP UDPServer;
	static byte packetBuffer[MAX_PACKET_SIZE];

	/* functions */
	static String readPackage (void);
};

#endif
