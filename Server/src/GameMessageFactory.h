#pragma once

#include <yojimbo.h>
#include "CSShared.h"

class GameMessageFactory : public yojimbo::MessageFactory
{
public:
    GameMessageFactory(yojimbo::Allocator& allocator) :
        MessageFactory(allocator, (int32_t)GameMessageType::COUNT)
    {}

    yojimbo::Message* CreateMessageInternal(int32_t type) {
        yojimbo::Message* message;
        yojimbo::Allocator& allocator = GetAllocator();
        (void)allocator;

        switch ((GameMessageType)type) {

        case GameMessageType::TEST: {
            message = YOJIMBO_NEW(allocator, TestMessage);
            if (!message)
                return nullptr;
            SetMessageType(message, (int32_t)GameMessageType::TEST);
            return message;
            break;
        }

        case GameMessageType::C2S_ChunkDataRequest: {
            message = YOJIMBO_NEW(allocator, ChunkDataRequest);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::C2S_ChunkDataRequest);
            return message;
            break;
        }

        case GameMessageType::S2C_CompressedChunkDataResponse: {
            message = YOJIMBO_NEW(allocator, ChunkDataResponse);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::S2C_CompressedChunkDataResponse);
            return message;
            break;
        }

        case GameMessageType::C2S_ConnectRequest: {
            message = YOJIMBO_NEW(allocator, ConnectRequestMessage);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::C2S_ConnectRequest);
            return message;
            break;
        }

        case GameMessageType::S2C_ConnectResponse: {
            message = YOJIMBO_NEW(allocator, ConnectResponseMessage);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::S2C_ConnectResponse);
            return message;
            break;
        }

        default: {
            return NULL;
        }

        }
    }

};
