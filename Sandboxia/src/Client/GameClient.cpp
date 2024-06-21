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
		//m_Client.HandleConnect(clientIndex);
	}
}

// override
void ClientAdapter::OnServerClientDisconnected(int32_t clientIndex) {
	if (m_Client != nullptr) {
		std::cout << "[WARNING] ClientAdapter::m_Client is not nullptr. This shouldnt happen ..." << std::endl;
		//m_Client.HandleDisconnect(clientIndex);
	}
}

GameClient::GameClient(const yojimbo::Address& serverAddress) :
	m_Adapter(std::make_unique<ClientAdapter>(ClientAdapter(this))),
	m_Client(yojimbo::GetDefaultAllocator(), yojimbo::Address("0.0.0.0"), m_ConnectionConfig, *m_Adapter, m_Time),
	m_Dispatcher(std::make_unique<ClientMessageDispatcher>(*this))
{
	uint64_t clientId;
	yojimbo_random_bytes((uint8_t*)&clientId, 8);
	m_Client.InsecureConnect(DEFAULT_PRIVATE_KEY, clientId, serverAddress);
}

void GameClient::Update(double deltaTime)
{
	// update client
	//std::cout << "[Client] m_Time = " << m_Time << std::endl;
	
	m_Client.ReceivePackets();

	if (m_Client.IsConnecting()) {
		if ((int32_t)(m_Time * 10) % 10 == 0) std::cout << "Connecting... " << m_Time << std::endl;
	}
	if (m_Client.IsConnected()) {
		SendMsgsToClientDispatcher();

		if (!m_bSentConnReq) {
			ConnectRequestMessage* request = (ConnectRequestMessage*)m_Client.CreateMessage((int32_t)GameMessageType::C2S_ConnectRequest);
			request->ClientVersion = 0;
			std::string playerName = "TestPlayer";
			strncpy_s(request->PlayerName, sizeof(request->PlayerName), playerName.c_str(), playerName.size());
			m_Client.SendMessage((int32_t)GameChannel::RELIABLE, request);

			m_bSentConnReq = true;
		}

		// ... do connected stuff ...

		/*
		// send a message when space is pressed
		if (KeyIsDown(Key::SPACE)) {
			TestMessage* message = (TestMessage*)m_Client.CreateMessage((int)GameMessageType::TEST);
			message->m_data = 42;
			m_Client.SendMessage((int)GameChannel::RELIABLE, message);
		}
		*/
		
	}

	m_Client.SendPackets();

	m_Time += deltaTime;
	//m_Client.AdvanceTime(m_Client.GetTime() + deltaTime);
	m_Client.AdvanceTime(m_Time);
}

//TODO: Ask here for help

ClientChunk GameClient::GetChunkFromQueue()
{
	if (m_ReceivedChunks.empty()) {
		return ClientChunk();
	}

	ClientChunk chunk = std::move(m_ReceivedChunks.front());
	m_ReceivedChunks.pop();
	return chunk;
}

void GameClient::RequestChunk(Vec3<int32_t> chunkPos)
{
	ChunkDataRequest* request = (ChunkDataRequest*)m_Client.CreateMessage((int32_t)GameMessageType::C2S_ChunkDataRequest);
	request->ChunkPos = chunkPos;
	m_Client.SendMessage((int32_t)GameChannel::RELIABLE, request);
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
	if (message->GetType() == (int32_t)GameMessageType::S2C_ConnectResponse) {
		std::cout << "[<] " << (int32_t)((ConnectResponseMessage*)message)->Status << std::endl;
	}

	switch ((GameMessageType)message->GetType())
	{
	case GameMessageType::S2C_CompressedChunkDataResponse: {
		ChunkDataResponse* response = (ChunkDataResponse*)message;
		std::shared_ptr<CompressedChunk> compressedChunk = response->S2C_CompressedChunkData;
		std::cout << "[Client] Received chunk Data: " << compressedChunk->Pos.GetX() << " " << compressedChunk->Pos.GetY() << " " << compressedChunk->Pos.GetZ() << "\n";

		ClientChunk chunk;
		chunk.Chunk = compressedChunk->ToChunk();

		if (chunk.Chunk) {
			m_GameClient.m_ReceivedChunks.push(chunk);
			Logger::GetInstance().Log(LogLevel::INFO, "[Client] Added chunk to the chunk pool");
		}
		else {
			Logger::GetInstance().Log(LogLevel::WARNING, "[Client] Failed to convert server-side chunk to client-side alternative");
		}
		break;
	}
	default:
		break;
	}
}