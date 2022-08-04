#include "io/UDPManager.hpp"
#include "system/Interface.hpp"

WiFiUDP UDPManager::UDPServer;
byte UDPManager::packetBuffer[MAX_PACKET_SIZE];

String UDPManager::readPackage (void)
{
	String myData = "";
	int cb = UDPServer.parsePacket();
	if (cb) {
		for (int i = 0; i < MAX_PACKET_SIZE; i++) packetBuffer[i] = 0;
		UDPServer.read(packetBuffer, cb);
		for (int i = 0; i < cb; i++) {
			myData += (char)packetBuffer[i];
		}
	}
	return myData;
}

void UDPManager::processCommand (String cmd)
{
	if (cmd.isEmpty()) return;
	cmd.toLowerCase();
	if (cmd.startsWith(CMD_MODE)) {
		WallMode m = Parser::parseWallMode(cmd);
		if (m != -1) Interface::setMode(m);
	}
	else if (cmd.startsWith(CMD_COLOR)) {
		CRGB color = Parser::parseColor(cmd);
		if (color.r != 0 || color.g != 0 || color.b != 0) {
			Interface::setColor(color);
			Interface::setColorMode(MONO);
		}
		else {
			ColorMode c = Parser::parseColorMode(cmd);
			if (c != -1) Interface::setColorMode(c);
		}
	}
	else if (cmd.startsWith(CMD_BRIGHTNESS)) {
		uint8_t value = (uint8_t) Parser::parseValue(cmd);
		Interface::setBrightness(value);
	}
}
