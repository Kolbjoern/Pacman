#include "Client.h"

#include <SFML/System.hpp>

#include "utils/Console.h"

void Client::run()
{
	init();

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

	disconnect();
	m_socket.unbind();
}

void Client::serverCall(std::function<void(void)> callback)
{
	m_startServer = callback;
}

void Client::connect(std::string& address, unsigned short port)
{
	m_server.address = address;
	m_server.port = port;

	m_socket.setBlocking(false);
	Network::bindSocket(m_socket);
	Network::registerToServer(m_socket, m_packet, m_server);
}

void Client::disconnect()
{
	Network::disconnectFromServer(m_socket, m_packet, m_server);
}

void Client::init()
{
	Console::print("(1) Singleplayer\n");
    Console::print("(2) Multiplayer\n");

    char arr[] = {'1', '2'};
    switch (Console::prompt(arr)) {
        case '1': {
        	m_startServer();
        	std::string address = sf::IpAddress::getLocalAddress().toString();
        	connect(address, SERVER_PORTNUM);
            break;
        }

        case '2':
            Console::print("(1) Host\n");
            Console::print("(2) Connect\n");

            switch (Console::prompt(arr)) {
                case '1': {
                	m_startServer();
        			std::string address = sf::IpAddress::getLocalAddress().toString();
        			connect(address, SERVER_PORTNUM);
                	break;
                }

                case '2': {
                	Console::print("Connect to IP: ");
    				std::string input = Console::prompt();
        			connect(input, SERVER_PORTNUM);
                	break;
                }
            }
            break;
    }

    m_window.create(sf::VideoMode(1024, 768), "pacman!");
	m_window.setFramerateLimit(60.0f);
}