#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Server
{
public:
	void run();
	void shutdown();

private:
	void init();

	sf::UdpSocket m_socket;
	sf::Mutex m_mutex;

	bool m_running;
};