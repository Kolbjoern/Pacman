#pragma once

#include <unordered_map>
#include <string>

#include <SFML/Network.hpp>

#define SERVER_PORTNUM 9966

struct Peer
{
	sf::IpAddress address;
	unsigned int port;
};

struct Net
{
	std::unordered_map<std::string, Peer> m_peers;
};

namespace NetManager
{
	void bindSocket(sf::UdpSocket &socket);
	void bindSocket(sf::UdpSocket &socket, unsigned short port);
	void registerClients(sf::UdpSocket &socket, sf::Packet &packet);
	void registerToServer(sf::UdpSocket &socket, sf::Packet &packet, Peer &server);
	void receive(sf::UdpSocket &socket, sf::Packet &packet);
};