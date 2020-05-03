#include "Server.h"

#include <iostream>

#include <SFML/System.hpp>

#define PORTNUM 9966

void Server::run()
{
	init();

	while(m_running) {
		std::cout << "SERVER::TICK" << std::endl;
		sf::sleep(sf::milliseconds(5000.0f));
	}
}

void Server::shutdown()
{
	//std::lock_guard<std::mutex> lock(m_mutex);
	sf::Lock lock(m_mutex);
	m_running = false;
}

void Server::init()
{
	std::cout << "SERVER::START" << std::endl;

	m_running = true;

	m_socket.setBlocking(false);

	if (m_socket.bind(PORTNUM) != sf::Socket::Done){
		std::cout << "SERVER::Could not bind socket" << std::endl;
	}

	std::cout << "public: " << sf::IpAddress::getPublicAddress() << std::endl;
	std::cout << "local: " << sf::IpAddress::getLocalAddress() << std::endl;
}