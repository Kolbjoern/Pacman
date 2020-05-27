#pragma once

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "net/Network.h"

class Client
{
public:
	void run();
	void serverCall(std::function<void(void)> callback);

private:
	void init();
	void connect(std::string& address, unsigned short port);
	void disconnect();

	std::function<void(void)> m_startServer;

	sf::RenderWindow m_window;
	sf::UdpSocket m_socket;
	sf::Packet m_packet;

	Peer m_server;
};