#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "net/Network.h"
#include "net/PacketManager.h"

enum class ServerState : unsigned int
{
	Idle = 0,
	Active = 1
};

class Server
{
public:
	void run();
	void startGame();
	void shutdown();

private:
	void init();

	sf::UdpSocket m_socket;
	sf::Packet m_packet;
	sf::Mutex m_mutex;

	ServerState m_state;
	PacketStates m_packetStates;

	bool m_running;
};