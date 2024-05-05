#pragma once
#include <yojimbo.h>

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
    }
};

