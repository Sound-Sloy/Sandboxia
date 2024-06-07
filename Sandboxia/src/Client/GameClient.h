#pragma once

#include <yojimbo.h>
#include <iostream>
#include <queue>

#include <Server/src/CSShared.h>
#include <Server/src/GameMessageFactory.h>

class GameClient;

class ClientAdapter : public yojimbo::Adapter
{
public:
    explicit ClientAdapter(GameClient* client = nullptr);
    yojimbo::MessageFactory* CreateMessageFactory(yojimbo::Allocator& allocator) override;
    void OnServerClientConnected(int32_t clientIndex) override;
    void OnServerClientDisconnected(int32_t clientIndex) override;
private:
    GameClient* m_Client = nullptr;
};
 
class ClientMessageDispatcher;

class GameClient {
public:
    GameClient(const yojimbo::Address& serverAddress);

    void Update(double deltaTime);

    std::shared_ptr<Chunk> GetChunkFromQueue();
    void RequestChunk(Vec3<int32_t> chunkPos);
private:
    GameConnectionConfig m_ConnectionConfig;
    std::unique_ptr<ClientAdapter> m_Adapter;
	yojimbo::Client m_Client;
    std::unique_ptr<ClientMessageDispatcher> m_Dispatcher;
    static const uint8_t DEFAULT_PRIVATE_KEY[yojimbo::KeyBytes];

    std::queue<std::shared_ptr<Chunk>> m_ReceivedChunks;

    double m_Time = 0.f;
    bool m_bSentConnReq = false;

    void SendMsgsToClientDispatcher();

    friend class ClientMessageDispatcher;
};

class ClientMessageDispatcher {
public:
    ClientMessageDispatcher(GameClient& gameClient);

    void DispatchMessage(yojimbo::Message* message);
private:
    GameClient& m_GameClient;
};

inline std::unique_ptr<GameClient> GGameClientInstance;