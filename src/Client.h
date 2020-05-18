#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "net/Network.h"

class Client
{
public:
	void run();
	void connect(std::string& address, unsigned short port);
	void disconnect();

private:
	void init();

	sf::RenderWindow m_window;
	sf::UdpSocket m_socket;
	sf::Packet m_packet;

	Peer m_server;
};