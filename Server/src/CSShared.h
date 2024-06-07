/// Client&Server Shared

// https://www.rogiel.com/en/blog/getting-started-with-asio-cpp-creating-tcp-gameServer
// https://github.com/mas-bandwidth/yojimbo/blob/main/USAGE.md
// https://github.com/mas-bandwidth/yojimbo/issues/25

#pragma once
#include <yojimbo.h>
#include "Messages.h"

// C2S = Client to Server
// S2C = Server to Client
enum class GameMessageType {
    TEST,
    C2S_ConnectRequest,
    S2C_ConnectResponse,
    Disconnect,
    C2S_ChunkDataRequest,
    S2C_CompressedChunkDataResponse,
    PlayerPos,
    COUNT
};

// two channels, one for each type that Yojimbo supports
enum class GameChannel {
    RELIABLE,
    UNRELIABLE,
    COUNT
};

struct GameConnectionConfig : yojimbo::ClientServerConfig {
    GameConnectionConfig() {
        numChannels = 2;
        channel[(int32_t)GameChannel::RELIABLE].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
        channel[(int32_t)GameChannel::UNRELIABLE].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
        maxPacketSize = 256 * 1024;
        maxPacketFragments = 256;
    }
};
