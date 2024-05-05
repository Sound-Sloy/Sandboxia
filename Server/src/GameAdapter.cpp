#include "GameAdapter.h"
#include "GameServer.h"

// explicit
GameAdapter::GameAdapter(GameServer* server) {
	m_GameServer = server;
}

// override
yojimbo::MessageFactory* GameAdapter::CreateMessageFactory(yojimbo::Allocator& allocator) {
	return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
}

// override
void GameAdapter::OnServerClientConnected(int clientIndex) {
	if (m_GameServer != nullptr) {
		m_GameServer->ClientConnected(clientIndex);
	}
}

// override
void GameAdapter::OnServerClientDisconnected(int clientIndex) {
	if (m_GameServer != nullptr) {
		m_GameServer->ClientDisconnected(clientIndex);
	}
}
