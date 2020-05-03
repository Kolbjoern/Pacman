#include "Game.h"

#include <iostream>
#include <string>
#include <thread>

#include "Server.h"
#include "Client.h"

void Game::start()
{
	std::cout << "(1) Singleplayer" << std::endl;
    std::cout << "(2) Multiplayer" << std::endl;

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
        Server server;
        sf::Thread serverThread(&Server::run, &server);
        serverThread.launch();

        Client client;
        client.run();

        server.shutdown();
        serverThread.wait();
    }
    else {
        std::cout << "(1) Host" << std::endl;
        std::cout << "(2) Connect" << std::endl;

        std::getline(std::cin, input);
        if (input == "1") {
            Server server;
            sf::Thread serverThread(&Server::run, &server);
            serverThread.launch();

            // start this when everyone is ready
            Client client;
            client.run();

            server.shutdown();
            serverThread.wait();
        }
        else {
            Client client;

            std::cout << "Connect to IP: ";
            std::getline(std::cin, input);

            client.connect(input);
            client.run();
        }
    }
}