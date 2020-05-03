#include "Client.h"

#include <iostream>

#include <SFML/System.hpp>

void Client::run()
{
	init();

	m_window.create(sf::VideoMode(1024, 768), "pacman!");
	m_window.setFramerateLimit(60.0f);

	sf::CircleShape circle(100.0f);
	circle.setFillColor(sf::Color::Red);

	while(m_window.isOpen()) {
		sf::Event event;
		while(m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
		}
		m_window.clear();
		m_window.draw(circle);
		m_window.display();
	}
}

void Client::connect(std::string &address)
{
	m_serverIp = address;
}

void Client::init()
{
	sf::Socket::Status status;
	status = m_socket.bind(sf::Socket::AnyPort);
	if (status != sf::Socket::Done) {
		std::cout << "CLIENT::Could not bind socket" << std::endl;
	}

	std::cout << "CLIENT::START" << std::endl;
}