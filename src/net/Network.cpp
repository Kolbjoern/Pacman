#include "Network.h"

#include "../utils/Console.h"

namespace Network
{
	void bindSocket(sf::UdpSocket& socket)
	{
		bindSocket(socket, sf::Socket::AnyPort);
	}

	void bindSocket(sf::UdpSocket& socket, unsigned short port)
	{
		sf::Socket::Status status;
		status = socket.bind(port);
		if (status != sf::Socket::Done) {
			Console::print("Could not bind to port: " + std::to_string(port) + "\n");
		}
	}

	void registerToServer(sf::UdpSocket& socket, sf::Packet& packet, Peer& server)
	{
		sf::Uint8 header = static_cast<int>(PacketHeader::Connect);
		packet << header;
		socket.send(packet, server.address, server.port);
		packet.clear();
	}

	void disconnectFromServer(sf::UdpSocket& socket, sf::Packet& packet, Peer& server)
	{
		sf::Uint8 header = static_cast<int>(PacketHeader::Disconnect);
		packet << header;
		socket.send(packet, server.address, server.port);
		packet.clear();
	}

	std::vector<PacketResult> receive(sf::UdpSocket& socket, sf::Packet& packet, PacketStates& states)
	{
		sf::IpAddress sender;
		unsigned short port;
		std::vector<PacketResult> res;

		// empty receive buffer
		while (socket.receive(packet, sender, port) == sf::Socket::Done) {
			res.push_back(PacketManager::processPacket(packet, sender, port, states));
		}

		return res;
	}

	std::string createUniqueId(sf::IpAddress& address, unsigned short port)
	{
		return address.toString() + ":" + std::to_string(port);
	}

	bool peerExists(std::unordered_map<std::string, Peer>& peers, std::string& uniqueId)
	{
		return peers.find(uniqueId) != peers.end();
	}
};