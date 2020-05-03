#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Client
{
public:
	void run();
	void connect(std::string &address);

private:
	void init();

	sf::RenderWindow m_window;
	sf::UdpSocket m_socket;
	sf::IpAddress m_serverIp;
};