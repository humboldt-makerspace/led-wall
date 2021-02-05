#ifndef UDP_MANAGER_HPP
#define UDP_MANAGER_HPP

#include "constants.h"
#include "WiFiUdp.h"

class UDPManager {
private:
	/* functions */

public:
	/* variables */
	static WiFiUDP UDPServer;
	static byte packetBuffer[MAX_PACKET_SIZE];

	/* functions */
	static String readPackage (void);
	static void processCommand (String cmd);
};

#endif
