#pragma once
#include "Chunk.h"


// a simple test message
enum class GameMessageType {
    TEST,
    ConnectRequest,
    ConnectResponse,
    Disconnect,
    ChunkData,
    PlayerPos,
    COUNT
};

// two channels, one for each type that Yojimbo supports
enum class GameChannel {
    RELIABLE,
    UNRELIABLE,
    COUNT
};

class TestMessage : public yojimbo::Message
{
public:
    int Data;

    TestMessage() :
        Data(0) {}

    template <typename Stream>
    bool Serialize(Stream& stream) {
        serialize_int(stream, Data, 0, 512);
        return true;
    }

    bool SerializeInternal(class yojimbo::ReadStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::WriteStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::MeasureStream& stream) {
        return Serialize(stream);
    };
};

class ChunkDataMessage : public yojimbo::BlockMessage
{
public:
    Chunk ChunkData;

    ChunkDataMessage() : ChunkData() {}

    template <typename Stream>
    bool Serialize(Stream& stream)
    {
        //serialize_bits(stream, Sequence, 16);
        serialize_object(stream, ChunkData);
        return true;
    }

    bool SerializeInternal(class yojimbo::ReadStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::WriteStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::MeasureStream& stream) {
        return Serialize(stream);
    };
};

class ConnectRequestMessage : public yojimbo::BlockMessage
{
public:
    std::string PlayerName;
    uint64_t PlayerEPOCH;
    uint32_t ClientVersion;

    ConnectRequestMessage() : PlayerName("0") {}

    template <typename Stream>
    bool Serialize(Stream& stream)
    {
        //serialize_bits(stream, Sequence, 16);
        serialize_object(stream, PlayerName);
        serialize_bits(stream, PlayerEPOCH, sizeof(PlayerEPOCH) * sizeof(uint8_t));
        serialize_bits(stream, ClientVersion, sizeof(ClientVersion) * sizeof(uint8_t));
        return true;
    }

    bool SerializeInternal(class yojimbo::ReadStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::WriteStream& stream) {
        return Serialize(stream);
    };
    bool SerializeInternal(class yojimbo::MeasureStream& stream) {
        return Serialize(stream);
    };
};