#pragma once

#include <vector>

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
	void shutdown();
	bool isRunning();

private:
	void init();
	void startGame();
	void unpack(std::vector<PacketResult>& results);
	void unpack(PacketResult& result);

	sf::UdpSocket m_socket;
	sf::Packet m_packet;
	sf::Mutex m_mutex;

	ServerState m_state;
	PacketStates m_packetStates;
	Net m_net;

	bool m_running;
};