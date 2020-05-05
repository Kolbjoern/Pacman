#include "Network.h"

#include "../utils/Console.h"

namespace Network
{
	void bindSocket(sf::UdpSocket &socket)
	{
		bindSocket(socket, sf::Socket::AnyPort);
	}

	void bindSocket(sf::UdpSocket &socket, unsigned short port)
	{
		sf::Socket::Status status;
		status = socket.bind(port);
		if (status != sf::Socket::Done) {
			Console::print("Could not bind to port: " + std::to_string(port) + "\n");
		}
	}

	void registerToServer(sf::UdpSocket &socket, sf::Packet &packet, Peer &server)
	{
		sf::Uint8 header = static_cast<int>(PacketHeader::Connect);
		packet << header;
		socket.send(packet, server.address, server.port);
		packet.clear();
	}

	void receive(sf::UdpSocket &socket, sf::Packet &packet, PacketStates &states)
	{
		sf::IpAddress sender;
		unsigned short port;

		// empty receive buffer
		while (socket.receive(packet, sender, port) == sf::Socket::Done) {
			PacketManager::processPacket(packet, sender, port, states);
		}
	}
};