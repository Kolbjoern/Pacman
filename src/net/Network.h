#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <SFML/Network.hpp>

#include "PacketManager.h"

#define SERVER_PORTNUM 9966

struct Peer
{
	sf::IpAddress address;
	unsigned int port;
};

struct Net
{
	std::unordered_map<std::string, Peer> peers;
};

namespace Network
{
	void bindSocket(sf::UdpSocket &socket);
	void bindSocket(sf::UdpSocket &socket, unsigned short port);
	void registerToServer(sf::UdpSocket &socket, sf::Packet &packet, Peer &server);
	void disconnectFromServer(sf::UdpSocket& socket, sf::Packet& packet, Peer& server);
	std::vector<PacketResult> receive(sf::UdpSocket &socket, sf::Packet &packet, PacketStates &states);
	std::string createUniqueId(sf::IpAddress& address, unsigned short port);
	bool peerExists(std::unordered_map<std::string, Peer>& peers, std::string& uniqueId);
};