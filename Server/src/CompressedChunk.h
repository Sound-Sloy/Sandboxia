#pragma once
#include <yojimbo.h>
#include "Chunk.h"
#include "CompressedBlock.h"

class CompressedChunk {
public:
	Vec2<int32_t> Pos = { 0,0 };
	CompressedBlock Blocks[CHUNK_VOLUME]{};
};