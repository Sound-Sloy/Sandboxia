#pragma once
#include <yojimbo.h>
#include <iostream>
#include "Chunk.h"
#include "CompressedBlock.h"

class CompressedChunk {
public:
	Vec3<int32_t> Pos = { 0,0,0 };
	//CompressedBlock Blocks[CHUNK_VOLUME]{};
	std::vector<CompressedBlock> Blocks = std::vector<CompressedBlock>(CHUNK_VOLUME);

	void FromChunk(Chunk chunk) {
		Pos = chunk.GetPos();
		for (int32_t i = 0; i < CHUNK_VOLUME; ++i) {
			Blocks[i].FromBlock(chunk.GetBlockByIndex(i));
		}
	}

	Chunk ToChunk() {
		Chunk chunk;
		chunk.SetPos(Pos);
		for (int32_t i = 0; i < sizeof(Blocks) / sizeof(CompressedBlock); ++i) {
			chunk.SetBlockAtIndex(i, Blocks[i].ToBlock());
		}
		return chunk;
	}

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, (uint8_t*)&Pos, sizeof(Pos));
		//serialize_bytes(stream, (uint8_t*)&Blocks, sizeof(Blocks));
		uint32_t size = static_cast<uint32_t>(Blocks.size()) * sizeof(CompressedBlock);
		serialize_uint32(stream, size);
		if (Stream::IsReading) {
			Blocks.resize(CHUNK_VOLUME);
		}
		serialize_bytes(stream, Blocks.data(), size);
		return true;
	}
};