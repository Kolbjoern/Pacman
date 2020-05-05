#include "PacketManager.h"

#include "../utils/Console.h"

namespace PacketManager
{
	void processPacket(sf::Packet &packet, sf::IpAddress &address, unsigned short port, PacketStates &states)
	{
		sf::Uint8 header;
		packet >> header;

		switch (static_cast<PacketHeader>(header)) {
			case PacketHeader::Connect:
				if (states.connect) {
					registerClient(address, port);
				}
				packet.clear();
				break;
		}
	}

	void registerClient(sf::IpAddress &address, unsigned short port)
	{
		Console::print("Client register: " + address.toString() + "::" + std::to_string(port) + "\n");
	}
}