#include "Server.h"

#include <SFML/System.hpp>

#include "utils/Console.h"

void Server::run()
{
	init();

	while (m_running) {
		switch (m_state) {
			case ServerState::Idle:
				Network::receive(m_socket, m_packet, m_packetStates);
				sf::sleep(sf::milliseconds(1000.0f));
				break;

			case ServerState::Active:
				Console::print("SERVER::TICK\n");
				Network::receive(m_socket, m_packet, m_packetStates);
				sf::sleep(sf::milliseconds(2500.0f));
				break;
		}
	}
}

void Server::startGame() 
{
	sf::Lock lock(m_mutex);
	m_state = ServerState::Active;
	m_packetStates.connect = false;
}

void Server::shutdown()
{
	sf::Lock lock(m_mutex); // sfml lock guard
	m_running = false;
}

void Server::init()
{
	Console::print("SERVER::START\n");

	m_running = true;
	m_state = ServerState::Idle;
	m_packetStates.connect = true;

	m_socket.setBlocking(false);
	Network::bindSocket(m_socket, SERVER_PORTNUM);

	Console::print("public: " + sf::IpAddress::getPublicAddress().toString() + "\n");
	Console::print("local: " + sf::IpAddress::getLocalAddress().toString() + "\n");
}