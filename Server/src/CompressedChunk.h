#pragma once
#include <yojimbo.h>
#include <iostream>
#include "Chunk.h"
#include "CompressedBlock.h"

class CompressedChunk {
public:
	Vec3<int32_t> Pos = { 0,0,0 };
	CompressedBlock Blocks[CHUNK_VOLUME]{};

	void FromChunk(std::shared_ptr<Chunk> chunk) {
		Pos = chunk->GetPos();
		for (int32_t i = 0; i < CHUNK_VOLUME; ++i) {
			Blocks[i].FromBlock(chunk->GetBlockByIndex(i));
		}
	}

	std::shared_ptr<Chunk> ToChunk() {
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->SetPos(Pos);
		for (int32_t i = 0; i < sizeof(Blocks) / sizeof(CompressedBlock); ++i) {
			chunk->SetBlockAtIndex(i, Blocks[i].ToBlock());
		}
		return chunk;
	}

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, (uint8_t*)&Pos, sizeof(Pos));
		serialize_bytes(stream, (uint8_t*)&Blocks, sizeof(Blocks));
		return true;
	}
};