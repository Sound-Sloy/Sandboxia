#include "GameClient.h"

const uint8_t GameClient::DEFAULT_PRIVATE_KEY[yojimbo::KeyBytes] = { 0 };

ClientAdapter::ClientAdapter(GameClient* client) :
	m_Client(client)
{
}

yojimbo::MessageFactory* ClientAdapter::CreateMessageFactory(yojimbo::Allocator& allocator) {
    return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
}

// override
void ClientAdapter::OnServerClientConnected(int32_t clientIndex) {
	if (m_Client != nullptr) {
		std::cout << "[WARNING] ClientAdapter::m_Client is not nullptr. This shouldnt happen ..." << std::endl;
		//m_Client->HandleConnect(clientIndex);
	}
}

// override
void ClientAdapter::OnServerClientDisconnected(int32_t clientIndex) {
	if (m_Client != nullptr) {
		std::cout << "[WARNING] ClientAdapter::m_Client is not nullptr. This shouldnt happen ..." << std::endl;
		//m_Client->HandleDisconnect(clientIndex);
	}
}

GameClient::GameClient(const yojimbo::Address& serverAddress) :
	m_Client(yojimbo::GetDefaultAllocator(), yojimbo::Address("0.0.0.0"), m_ConnectionConfig, *m_Adapter, 0.0),
	m_Dispatcher(std::make_unique<ClientMessageDispatcher>(ClientMessageDispatcher(*this)))
{
	uint64_t clientId;
	yojimbo_random_bytes((uint8_t*)&clientId, 8);
	m_Client.InsecureConnect(DEFAULT_PRIVATE_KEY, clientId, serverAddress);
}

void GameClient::Update(float deltaTime)
{
	// update client
	m_Client.AdvanceTime(m_Client.GetTime() + deltaTime);
	m_Client.ReceivePackets();

	if (m_Client.IsConnected()) {
		SendMsgsToClientDispatcher();

		// ... do connected stuff ...

		/*
		// send a message when space is pressed
		if (KeyIsDown(Key::SPACE)) {
			TestMessage* message = (TestMessage*)m_Client.CreateMessage((int)GameMessageType::TEST);
			message->m_data = 42;
			m_Client.SendMessage((int)GameChannel::RELIABLE, message);
		}
		*/
		ConnectRequestMessage* request = (ConnectRequestMessage*)m_Client.CreateMessage((int32_t)GameMessageType::C2S_ConnectRequest);
		request->ClientVersion = 0;
		std::string playerName = "TestPlayer";
		strncpy_s(request->PlayerName, sizeof(request->PlayerName), playerName.c_str(), playerName.size());
		m_Client.SendMessage((int32_t)GameChannel::RELIABLE, request);
		delete request;
		request = nullptr;
	}

	m_Client.SendPackets();
}

void GameClient::SendMsgsToClientDispatcher() {
	for (int32_t channelIndex = 0; channelIndex < m_ConnectionConfig.numChannels; channelIndex++) {
		yojimbo::Message* message = m_Client.ReceiveMessage(channelIndex);
		while (message != NULL) {
			m_Dispatcher->DispatchMessage(message);
			m_Client.ReleaseMessage(message);
			message = m_Client.ReceiveMessage(channelIndex);
		}
	}
}

ClientMessageDispatcher::ClientMessageDispatcher(GameClient& gameClient) :
	m_GameClient(gameClient)
{}

void ClientMessageDispatcher::DispatchMessage(yojimbo::Message* message) {

}