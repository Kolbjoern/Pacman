#pragma once

#include <SFML/Network.hpp>

enum class PacketHeader : unsigned short int
{
	Connect = 0,
	Disconnect = 1
};

struct PacketStates
{
	bool connect = false;
};

struct PacketResult
{
	bool success = false;
	PacketHeader type;
	void* data;
};

struct ConnectData
{
	sf::IpAddress address;
	unsigned short port;
};

namespace PacketManager
{
	PacketResult processPacket(sf::Packet& packet, sf::IpAddress& address, unsigned short port, PacketStates& states);
	PacketResult processConnect(sf::IpAddress& address, unsigned short port);
	PacketResult processDisconnect(sf::IpAddress& address, unsigned short port);
};