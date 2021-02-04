#include "io/UDPManager.hpp"
#include "system/Interface.hpp"

WiFiUDP UDPManager::UDPServer;
byte UDPManager::packetBuffer[MAX_PACKET_SIZE];

String UDPManager::readPackage (void)
{
	String myData = "";
	int cb = UDPManager::UDPServer.parsePacket();
	if (cb) {
		for (int i = 0; i < MAX_PACKET_SIZE; i++) packetBuffer[i] = 0;
		UDPManager::UDPServer.read(packetBuffer, MAX_PACKET_SIZE);
		for (int i = 0; i < cb; i++) {
			myData += (char)packetBuffer[i];
		}
	}
	return myData;
}
