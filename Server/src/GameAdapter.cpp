#include "GameAdapter.h"
#include "GameServer.h"

// explicit
GameAdapter::GameAdapter(GameServer* server) {
	m_Server = server;
}

// override
yojimbo::MessageFactory* GameAdapter::CreateMessageFactory(yojimbo::Allocator& allocator) {
	return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
}

// override
void GameAdapter::OnServerClientConnected(int clientIndex) {
	if (m_Server != nullptr) {
		m_Server->ClientConnected(clientIndex);
	}
}

// override
void GameAdapter::OnServerClientDisconnected(int clientIndex) {
	if (m_Server != nullptr) {
		m_Server->ClientDisconnected(clientIndex);
	}
}
