#pragma once

#include <cstdlib>
#include <vector>
#include "Block.h"
#include "Vec2.h"
#include "Vec3.h"

#define CHUNK_VOLUME (32*256*32)
#define CHUNK_SIZE_VEC3 Vec3(32,256,32)
#define CHUNK_SIZE_VEC3_I64 Vec3<int64_t>(32,256,32)
#define REGION_SIZE_CHUNKS_AXIS 32

class Chunk {
public:
	void SetBlock(Vec3<uint16_t> blockPos, Block block);
	Block GetBlock(Vec3<uint16_t> blockPos) const;

	void SetPos(Vec2<int32_t> pos);
	Vec2<int32_t> GetPos() const;

	constexpr static uint32_t GetBlockIndexInChunk(Vec3<uint16_t> blockPos);
	constexpr static Vec3<uint16_t> GetBlockPosInChunk(Vec3<int64_t> blockPos);

	constexpr inline Vec2<int32_t> GetRegion() const;
private:
	Vec2<int32_t> m_Pos = { 0,0 };
	Block Blocks[CHUNK_VOLUME]{};
};