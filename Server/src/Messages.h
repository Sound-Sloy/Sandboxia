#pragma once
#include "Chunk.h"
#include "CompressedChunk.h"

class TestMessage : public yojimbo::Message
{
public:
    int32_t Data;

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
    CompressedChunk S2C_CompressedChunkDataResponse;

    ChunkDataMessage() : S2C_CompressedChunkDataResponse() {}

    template <typename Stream>
    bool Serialize(Stream& stream)
    {
        //serialize_bits(stream, Sequence, 16);
        serialize_object(stream, S2C_CompressedChunkDataResponse);
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

class ConnectRequestMessage : public yojimbo::Message
{
public:
    char PlayerName[128] = {0};
    uint64_t PlayerEPOCH;
    uint32_t ClientVersion;

    ConnectRequestMessage() : PlayerName("0") {}

    template <typename Stream>
    bool Serialize(Stream& stream)
    {
        //serialize_bits(stream, Sequence, 16);
        serialize_bytes(stream, (uint8_t*)&PlayerName, sizeof(PlayerName));
        serialize_bytes(stream, (uint8_t*)&PlayerEPOCH, sizeof(PlayerEPOCH));
        serialize_bytes(stream, (uint8_t*)&ClientVersion, sizeof(ClientVersion));
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

enum class ConnectionStatus : uint8_t {
    ConnectionOK,
    InvalidPlayername,
    InvalidEPOCH,
    OutdatedClient,
    CancelledByServer,
    AlreadyConnected,
    NONE,
    ENUM_CNT
};

class ConnectResponseMessage : public yojimbo::Message
{
public:
    ConnectionStatus Status = ConnectionStatus::NONE;
    const char* Data = nullptr;

    ConnectResponseMessage() = default;

    template <class Stream>
    bool Serialize(Stream& stream) {
        serialize_bytes(stream, (uint8_t*)&Status, sizeof(Status));
        if (Status == ConnectionStatus::CancelledByServer) {

        }
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