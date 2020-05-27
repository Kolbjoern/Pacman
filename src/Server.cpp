#include "Server.h"

#include "utils/Console.h"

void Server::run()
{
	init();

	while (m_running) {
		switch (m_state) {
			case ServerState::Idle: {
				std::vector<PacketResult> result;
				result = Network::receive(m_socket, m_packet, m_packetStates);
				unpack(result);
				sf::sleep(sf::milliseconds(2000.0f));
				break;
			}

			case ServerState::Active:
				Console::print("SERVER::TICK\n");
				std::vector<PacketResult> result;
				result = Network::receive(m_socket, m_packet, m_packetStates);
				unpack(result);
				sf::sleep(sf::milliseconds(2500.0f));
				break;
		}
	}
}

void Server::startGame() 
{
	sf::Lock lock(m_mutex);

	// clear receive buffer first
	std::vector<PacketResult> result;
	result = Network::receive(m_socket, m_packet, m_packetStates);
	unpack(result);
	
	m_state = ServerState::Active;
	m_packetStates.connect = false;
}

void Server::shutdown()
{
	sf::Lock lock(m_mutex); // sfml lock guard
	m_running = false;
	m_socket.unbind();
}

bool Server::isRunning()
{
	return m_running;
}

void Server::init()
{
	Console::print("SERVER::START\n");

	m_running = true;
	m_state = ServerState::Idle;
	m_packetStates.connect = true;

	m_socket.setBlocking(false);
	Network::bindSocket(m_socket, SERVER_PORTNUM);

	Console::print("public: " + sf::IpAddress::getPublicAddress().toString() + "\n");
	Console::print("local: " + sf::IpAddress::getLocalAddress().toString() + "\n");
}

void Server::unpack(std::vector<PacketResult>& r)
{
	for (std::vector<PacketResult>::iterator it = std::begin(r); it != std::end(r); ++it) {
		unpack(*it);
	}
}

void Server::unpack(PacketResult& result)
{
	if (result.success == false) {
		return;
	}
	
	switch (result.type) {
		case PacketHeader::Connect: {
			ConnectData* tp = static_cast<ConnectData*>(result.data);
			
			std::string uniqueId = Network::createUniqueId(tp->address, tp->port);

			Peer p;
			p.address = tp->address;
			p.port = tp->port;
			m_net.peers.emplace(uniqueId, p);

			Console::print("Num peers: " + std::to_string(m_net.peers.size()) + "\n");
			delete tp;
			break;
		}

		case PacketHeader::Disconnect: {
			ConnectData* tp = static_cast<ConnectData*>(result.data);

			std::string uniqueId = Network::createUniqueId(tp->address, tp->port);

			if (Network::peerExists(m_net.peers, uniqueId)) {
				m_net.peers.erase(uniqueId);
			}
			Console::print("Num peers: " + std::to_string(m_net.peers.size()) + "\n");
			delete tp;
			break;
		}
	}
}