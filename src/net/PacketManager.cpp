#include "PacketManager.h"

#include "../utils/Console.h"

namespace PacketManager
{
	PacketResult processPacket(sf::Packet &packet, sf::IpAddress &address, unsigned short port, PacketStates &states)
	{
		sf::Uint8 header;
		packet >> header;
		PacketResult res;

		switch (static_cast<PacketHeader>(header)) {
			case PacketHeader::Connect:
				if (states.connect) {
					res = processConnect(address, port);
				}
				packet.clear();
				break;

			case PacketHeader::Disconnect:
				res = processDisconnect(address, port);
				packet.clear();
				break;
		}
		return res;
	}

	PacketResult processConnect(sf::IpAddress &address, unsigned short port)
	{
		Console::print("Client register: " + address.toString() + "::" + std::to_string(port) + "\n");

		PacketResult result;
		result.success = true;
		result.type = PacketHeader::Connect;

		ConnectData* t = new ConnectData();
		t->address = address;
		t->port = port;

		result.data = static_cast<void*>(t);

		return result;
	}

	PacketResult processDisconnect(sf::IpAddress &address, unsigned short port)
	{
		Console::print("Client disconnected: " + std::to_string(port) + "\n");

		PacketResult result;
		result.success = true;
		result.type = PacketHeader::Disconnect;

		ConnectData* t = new ConnectData();
		t->address = address;
		t->port = port;

		result.data = static_cast<void*>(t);

		return result;
	}
}