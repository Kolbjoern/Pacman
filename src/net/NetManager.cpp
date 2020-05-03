#include "NetManager.h"

#include "PacketHeader.h"
#include "../utils/Console.h"

namespace NetManager
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

	void registerClients(sf::UdpSocket &socket, sf::Packet &packet)
	{
		sf::IpAddress sender;
		unsigned short port;
		sf::Uint8 header;

		// empty receive buffer
		while(socket.receive(packet, sender, port) == sf::Socket::Done) {
			packet >> header;

			switch(static_cast<PacketHeader>(header)) {
				case PacketHeader::Register:
					packet.clear();
					Console::print("Client register: " + sender.toString() + "::" + std::to_string(port) + "\n");
					break;
			}
		}
	}

	void registerToServer(sf::UdpSocket &socket, sf::Packet &packet, sf::IpAddress &serverAddress, unsigned short port)
	{
		sf::Uint8 header = static_cast<int>(PacketHeader::Register);
		packet << header;
		socket.send(packet, serverAddress, port);
		packet.clear();
	}

	void receive(sf::UdpSocket &socket, sf::Packet &packet)
	{

	}
};