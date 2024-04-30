#include "Networking.h"


GameServer::GameServer(const yojimbo::Address& address) :
	m_Adapter(this), m_Server(yojimbo::GetDefaultAllocator(), DEFAULT_PRIVATE_KEY, address, m_ConnectionConfig, m_Adapter, 0.0)
{
	m_Server.Start(MAX_PLAYERS);
	if (!m_Server.IsRunning()) {
		throw std::runtime_error("Could not start server on port " + std::to_string(address.GetPort()));
	}

	std::array<char, 256> buf;
	m_Server.GetAddress().ToString(buf.data(), buf.size());
	std::cout << "Server address is " << buf.data() << std::endl;

	/// TODO: LOAD GAME
	/// ...
}

void GameServer::ClientConnected(int32_t clientIndex) {
	std::cout << "Client " << clientIndex << " connected" << std::endl;
}

void GameServer::ClientDisconnected(int32_t clientIndex) {
	std::cout << "Client " << clientIndex << " disconnected" << std::endl;
}

void GameServer::Run() {
	float fixedDt = 1.0f / TICK_RATE;
	while (m_bRunning) {
		double currentTime = yojimbo_time();
		if (m_Time <= currentTime) {
			Update(fixedDt);
			m_Time += fixedDt;
		}
		else {
			yojimbo_sleep(m_Time - currentTime);
		}
	}
}

void GameServer::Update(float deltaTime) {
	// stop if server is not running
	if (!m_Server.IsRunning()) {
		m_bRunning = false;
		return;
	}

	// update server and process messages
	m_Server.AdvanceTime(m_Time);
	m_Server.ReceivePackets();
	SendMsgsToDispatcher();

	// ... process client inputs ...
	// ... update game ...
	// ... send game state to clients ...

	m_Server.SendPackets();
}

void GameServer::SendMsgsToDispatcher() {
	for (uint32_t clientIndex = 0; clientIndex < MAX_PLAYERS; clientIndex++) {
		if (!m_Server.IsClientConnected(clientIndex)) {
			continue;
		}
		for (uint32_t channelIndex = 0; channelIndex < m_ConnectionConfig.numChannels; channelIndex++) {
			yojimbo::Message* message = m_Server.ReceiveMessage(clientIndex, channelIndex);
			while (message != nullptr) {
				m_Dispatcher->DispatchMessage(clientIndex, message);
				m_Server.ReleaseMessage(clientIndex, message);
				message = m_Server.ReceiveMessage(clientIndex, channelIndex);
			}
		}
	}
}
