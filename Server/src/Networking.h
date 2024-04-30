#pragma once

#include <iostream>
#include <string>
#include <yojimbo.h>
#include <array>

#include "Chunk.h"
#include "Messages.h"
#include "MessageDispatcher.h"


// https://www.rogiel.com/en/blog/getting-started-with-asio-cpp-creating-tcp-server
// https://github.com/mas-bandwidth/yojimbo/blob/main/USAGE.md
// https://github.com/mas-bandwidth/yojimbo/issues/25

// the client and server config
struct GameConnectionConfig : yojimbo::ClientServerConfig {
    GameConnectionConfig() {
        numChannels = 2;
        channel[(int32_t)GameChannel::RELIABLE].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
        channel[(int32_t)GameChannel::UNRELIABLE].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
    }
};

// the adapter
class GameAdapter : public yojimbo::Adapter
{
public:
    explicit GameAdapter(GameServer* server = nullptr) :
        m_Server(server) {}

    yojimbo::MessageFactory* CreateMessageFactory(yojimbo::Allocator& allocator) override {
        return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
    }

    void OnServerClientConnected(int clientIndex) override {
        if (m_Server != nullptr) {
            m_Server->ClientConnected(clientIndex);
        }
    }

    void OnServerClientDisconnected(int clientIndex) override {
        if (m_Server != nullptr) {
            m_Server->ClientDisconnected(clientIndex);
        }
    }

private:
    GameServer* m_Server;
};

// the message factory
//YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int)GameMessageType::COUNT);
//YOJIMBO_DECLARE_MESSAGE_TYPE((int)GameMessageType::TEST, TestMessage);
//YOJIMBO_MESSAGE_FACTORY_FINISH();

class GameMessageFactory : public yojimbo::MessageFactory
{
public:
    GameMessageFactory(yojimbo::Allocator& allocator) :
        MessageFactory(allocator, (int32_t)GameMessageType::COUNT)
    {
    }

    yojimbo::Message* CreateMessageInternal(int32_t type) {
        yojimbo::Message* message;
        yojimbo::Allocator& allocator = GetAllocator();
        (void)allocator;
        
        switch ((GameMessageType)type){

        case GameMessageType::TEST: {
            message = YOJIMBO_NEW(allocator, TestMessage);
            if (!message)
                return nullptr;
            SetMessageType(message, (int32_t)GameMessageType::TEST);
            return message;
            break;
        }

        case GameMessageType::ChunkData: {
            message = YOJIMBO_NEW(allocator, ChunkDataMessage);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::ChunkData);
            return message;
            break;
        }
                
        default: {
            return NULL;
        }

        }
    }

};


class GameServer {
public:
    GameServer(const yojimbo::Address& address);

    void ClientConnected(int32_t clientIndex);
    void ClientDisconnected(int32_t clientIndex);

    void Run();
    void Update(float deltaTime);
private:
    GameAdapter m_Adapter;
    yojimbo::Server m_Server;
    GameConnectionConfig m_ConnectionConfig;
    std::unique_ptr<MessageDispatcher> m_Dispatcher;

    static const uint8_t DEFAULT_PRIVATE_KEY[yojimbo::KeyBytes];
    static const uint32_t MAX_PLAYERS = 64;
    static const uint32_t TICK_RATE = 20;

    bool m_bRunning = true;
    double m_Time = 0;

    void SendMsgsToDispatcher();
};