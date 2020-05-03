#include "Server.h"

#include <SFML/System.hpp>

#include "net/NetManager.h"
#include "utils/Console.h"

#define PORTNUM 9966

void Server::run()
{
	init();

	while(m_registering && m_running) {
		sf::sleep(sf::milliseconds(1000.0f));
		NetManager::registerClients(m_socket, m_packet);
	}

	while(m_running) {
		Console::print("SERVER::TICK\n");
		NetManager::receive(m_socket, m_packet);
		sf::sleep(sf::milliseconds(2500.0f));
	}
}

void Server::startGame()
{
	sf::Lock lock(m_mutex);
	m_registering = false;
}

void Server::shutdown()
{
	sf::Lock lock(m_mutex); // sfml lock guard
	m_running = false;
}

void Server::init()
{
	Console::print("SERVER::START\n");

	m_registering = true;
	m_running = true;

	m_socket.setBlocking(false);
	NetManager::bindSocket(m_socket, PORTNUM);

	Console::print("public: " + sf::IpAddress::getPublicAddress().toString() + "\n");
	Console::print("local: " + sf::IpAddress::getLocalAddress().toString() + "\n");
}