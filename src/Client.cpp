#include "Client.h"

#include <SFML/System.hpp>

#include "utils/Console.h"

void Client::run()
{
	init();

	m_window.create(sf::VideoMode(1024, 768), "pacman!");
	m_window.setFramerateLimit(60.0f);

	sf::CircleShape circle(100.0f);
	circle.setFillColor(sf::Color::Red);

	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
		}
		m_window.clear();
		m_window.draw(circle);
		m_window.display();
	}
}

void Client::connect(std::string &address, unsigned short port)
{
	m_server.address = address;
	m_server.port = port;

	m_socket.setBlocking(false);
	Network::bindSocket(m_socket);
	Network::registerToServer(m_socket, m_packet, m_server);
}

void Client::init()
{
	Console::print("CLIENT::START\n");
}