#include "Game.h"

#include <string>
#include <thread>

#include "Server.h"
#include "Client.h"
#include "utils/Console.h"

void Game::start()
{
    Console::print("(1) Singleplayer\n");
    Console::print("(2) Multiplayer\n");

    char arr[] = {'1', '2'};
    switch (Console::prompt(arr)) {
        case '1':
            startSingleplayer();
            break;

        case '2':
            Console::print("(1) Host\n");
            Console::print("(2) Connect\n");

            switch (Console::prompt(arr)) {
                case '1': startMultiplayerAsHost(); break;
                case '2': startMultiplayerAsPeer(); break;
            }
            break;
    }
}

void Game::startSingleplayer()
{
    Server server;
    sf::Thread serverThread(&Server::run, &server);
    serverThread.launch();

    Client client;
    std::string address = "10.0.0.2";
    client.connect(address, 9966);

    server.startGame();

    client.run();

    server.shutdown();
    serverThread.wait();
}

void Game::startMultiplayerAsHost()
{
    Server server;
    sf::Thread serverThread(&Server::run, &server);
    serverThread.launch();

    std::string address = "10.0.0.2";
    Client client;
    client.connect(address, 9966);

    // wait for other clients to connect
    std::string input;
    while(input != "start") {
        input = Console::prompt();
    }
    server.startGame();
    client.run();

    server.shutdown();
    serverThread.wait();
}

void Game::startMultiplayerAsPeer()
{
    Console::print("Connect to IP: ");
    
    std::string input = Console::prompt();

    Client client;
    client.connect(input, 9966);
    client.run();
}