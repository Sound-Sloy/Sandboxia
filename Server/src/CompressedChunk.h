#pragma once
#include <yojimbo.h>
#include "Chunk.h"
#include "CompressedBlock.h"

class CompressedChunk {
public:
	Vec2<int32_t> Pos = { 0,0 };
	CompressedBlock Blocks[CHUNK_VOLUME]{};

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, (uint8_t*)&Pos, sizeof(Pos));
		serialize_bytes(stream, (uint8_t*)&Blocks, sizeof(Blocks));
		return true;
	}
};