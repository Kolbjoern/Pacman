#include "Game.h"

#include "Server.h"
#include "Client.h"

void startServer(sf::Thread& sthread)
{
    sthread.launch();
}

void Game::start()
{
    Server server;
    sf::Thread serverThread(&Server::run, &server);

    Client client;
    client.serverCall([&]() {
        startServer(serverThread); 
    });
    client.run();

    if (server.isRunning()) {
        server.shutdown();
        serverThread.wait();
    }    
}