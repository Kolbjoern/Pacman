#pragma once

#include <SFML/Network.hpp>

struct PacketStates
{
	bool connect = false;
};

enum class PacketHeader : unsigned short int
{
	Connect = 0
};

namespace PacketManager
{
	void processPacket(sf::Packet &packet, sf::IpAddress &address, unsigned short port, PacketStates &states);
	void registerClient(sf::IpAddress &address, unsigned short port);
};