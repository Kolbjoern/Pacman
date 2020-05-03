#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Server
{
public:
	void run();
	void startGame();
	void shutdown();

private:
	void init();
	void registering();

	sf::UdpSocket m_socket;
	sf::Packet m_packet;
	sf::Mutex m_mutex;

	bool m_registering;
	bool m_running;
};