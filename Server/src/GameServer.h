#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <yojimbo.h>
#include "CSShared.h"
#include "Player.h"

class GameAdapter;

class MessageDispatcher;

class GameServer {
public:
    GameServer(const yojimbo::Address& address);

    void ClientConnected(int32_t clientIndex);
    void ClientDisconnected(int32_t clientIndex);

    void Run();
    void Update(float deltaTime);
private:
    std::unique_ptr<GameAdapter> m_Adapter;
    GameConnectionConfig m_ConnectionConfig;
    yojimbo::Server m_Server;
    std::unique_ptr<MessageDispatcher> m_Dispatcher;

    static const uint8_t DEFAULT_PRIVATE_KEY[yojimbo::KeyBytes];
    static const uint32_t MAX_PLAYERS = 64;
    static const uint32_t TICK_RATE = 20;
    static const uint32_t REQUIRED_CLIENT_VERSION = 0;

    std::vector<Player> m_PlayerList;

    bool m_bRunning = true;
    double m_Time = 0.f;

    void SendMsgsToDispatcher();

    bool ValidatePlayerName(char playerName[128]);
    bool IsPlayerBanned(char playerName[128]);

    friend class MessageDispatcher;
};


class MessageDispatcher {
public:
    MessageDispatcher(GameServer& gameServer);
    //~MessageDispatcher() = default; deleted bc of reference

    void DispatchMessage(uint32_t clientIndex, yojimbo::Message* message);
private:
    GameServer& m_Server;
    bool m_bInitialized = false;
};