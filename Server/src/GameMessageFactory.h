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

        case GameMessageType::S2C_CompressedChunkDataResponse: {
            message = YOJIMBO_NEW(allocator, ChunkDataMessage);
            if (!message) {
                return nullptr;
            }
            SetMessageType(message, (int32_t)GameMessageType::S2C_CompressedChunkDataResponse);
            return message;
            break;
        }

        default: {
            return NULL;
        }

        }
    }

};