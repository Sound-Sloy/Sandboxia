#pragma once

#include <yojimbo.h>
#include <cstdint>

#include "ClientServerConfig.h"

class GameClient;

class ClientAdapter : public yojimbo::Adapter
{
public:
    explicit ClientAdapter(GameClient* client = nullptr);

    yojimbo::MessageFactory* CreateMessageFactory(yojimbo::Allocator& allocator) override;

    void OnServerClientConnected(int clientIndex) override;

    void OnServerClientDisconnected(int clientIndex) override;

private:
    GameClient* m_GameClient = nullptr;
};

class GameClient {
public:
    GameClient(const yojimbo::Address& serverAddress);

private:
    GameConnectionConfig m_ConnectionConfig;
    ClientAdapter* m_Adapter = nullptr;
	yojimbo::Client* m_Client;

};