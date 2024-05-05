#pragma once
#include <yojimbo.h>
#include "GameMessageFactory.h"

// Fw declare GameServer
class GameServer;

// the adapter
class GameAdapter : public yojimbo::Adapter
{
public:
    explicit GameAdapter(GameServer* server = nullptr);

    yojimbo::MessageFactory* CreateMessageFactory(yojimbo::Allocator& allocator) override;

    void OnServerClientConnected(int clientIndex) override;

    void OnServerClientDisconnected(int clientIndex) override;

private:
    GameServer* m_GameServer = nullptr;
};