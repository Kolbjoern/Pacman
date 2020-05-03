#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Client
{
public:
	void run();
	void connect(std::string &address, unsigned short port);

private:
	void init();

	sf::RenderWindow m_window;
	sf::UdpSocket m_socket;
	sf::Packet m_packet;
	sf::IpAddress m_serverAddress;

	unsigned short m_serverPort;
};