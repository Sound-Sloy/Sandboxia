#include "Networking.h"


GameServer::GameServer(const yojimbo::Address& address) :
	m_Adapter(this), m_GameServer(yojimbo::GetDefaultAllocator(), DEFAULT_PRIVATE_KEY, address, m_ConnectionConfig, m_Adapter, 0.0)
{
	m_GameServer.Start(MAX_PLAYERS);
	if (!m_GameServer.IsRunning()) {
		throw std::runtime_error("Could not start server on port " + std::to_string(address.GetPort()));
	}

	std::array<char, 256> buf;
	m_GameServer.GetAddress().ToString(buf.data(), buf.size());
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
	if (!m_GameServer.IsRunning()) {
		m_bRunning = false;
		return;
	}

	// update server and process messages
	m_GameServer.AdvanceTime(m_Time);
	m_GameServer.ReceivePackets();
	SendMsgsToDispatcher();

	// ... process client inputs ...
	// ... update game ...
	// ... send game state to clients ...

	m_GameServer.SendPackets();
}

void GameServer::SendMsgsToDispatcher() {
	for (uint32_t clientIndex = 0; clientIndex < MAX_PLAYERS; clientIndex++) {
		if (!m_GameServer.IsClientConnected(clientIndex)) {
			continue;
		}
		for (uint32_t channelIndex = 0; channelIndex < m_ConnectionConfig.numChannels; channelIndex++) {
			yojimbo::Message* message = m_GameServer.ReceiveMessage(clientIndex, channelIndex);
			while (message != nullptr) {
				m_Dispatcher->DispatchMessage(clientIndex, message);
				m_GameServer.ReleaseMessage(clientIndex, message);
				message = m_GameServer.ReceiveMessage(clientIndex, channelIndex);
			}
		}
	}
}

// this is ugly
bool GameServer::ValidatePlayerName(char playerName[128])
{
	bool found = false;
	for (int32_t i = 127; i >= 0; --i) {
		if (   ((int32_t)playerName[i] >= 48 and (int32_t)playerName[i] <= 57)	/* 12345... */
			or ((int32_t)playerName[i] >= 64 and (int32_t)playerName[i] <= 90)  /* ABCDE... */
			or ((int32_t)playerName[i] >= 97 and (int32_t)playerName[i] <= 122) /* abcde... */
			or ((int32_t)playerName[i] == 95))									/* _ */
		{
			found = true;
		}
		else {
			if (found) {
				return false;
			}
		}
	}
	if (!found) {
		return false;
	}

	// if first letter is not a->Z

	if (    ((int32_t)playerName[0] < 64 or (int32_t)playerName[0] > 90)	/* ABCDE... */
		and ((int32_t)playerName[0] < 97 or (int32_t)playerName[0] > 122))	/* abcde... */
	{
		return false;
	}

	return true;
}

// TO DO:
bool GameServer::IsPlayerBanned(char playerName[128])
{
	return false;
}


MessageDispatcher::MessageDispatcher(GameServer& gameServer) :
	m_GameServer(gameServer)
{
	m_bInitialized = true;
}

void MessageDispatcher::DispatchMessage(uint32_t clientIndex, yojimbo::Message* message) {
	switch ((GameMessageType)message->GetType()) {
	case GameMessageType::C2S_ConnectRequest: {
		ConnectRequestMessage* request = (ConnectRequestMessage*)message;
		ConnectResponseMessage* response = (ConnectResponseMessage*)m_GameServer.m_GameServer.CreateMessage(clientIndex, (int32_t)GameMessageType::S2C_ConnectResponse);
		bool responseSet = false;
		if (!m_GameServer.ValidatePlayerName(request->PlayerName)) {
			response->Status = ConnectionStatus::InvalidPlayername;
			m_GameServer.m_GameServer.SendMessage(clientIndex, (int32_t)GameChannel::RELIABLE, response);
			break;
		}
		if (request->ClientVersion != m_GameServer.REQUIRED_CLIENT_VERSION) {
			response->Status = ConnectionStatus::OutdatedClient;
			m_GameServer.m_GameServer.SendMessage(clientIndex, (int32_t)GameChannel::RELIABLE, response);
			break;
		}
		// TO DO: Some check with epoch

		if (m_GameServer.IsPlayerBanned(request->PlayerName)) {
			response->Status = ConnectionStatus::CancelledByServer;
			m_GameServer.m_GameServer.SendMessage(clientIndex, (int32_t)GameChannel::RELIABLE, response);
			break;
		}
		
		response->Status = ConnectionStatus::ConnectionOK;
		m_GameServer.m_GameServer.SendMessage(clientIndex, (int32_t)GameChannel::RELIABLE, response);
		break;
	}
	}
}