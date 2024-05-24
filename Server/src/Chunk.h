#pragma once

#include <cstdlib>
#include <vector>
#include "Block.h"
#include <shared/utils/Vec2.h>
#include <shared/utils/Vec3.h>

#define CHUNK_VOLUME (32*32*32)
#define CHUNK_SIZE_VEC3 Vec3(32,32,32)
#define CHUNK_SIZE_VEC3_I64 Vec3<int64_t>(32,32,32)
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

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, m_Pos, sizeof(m_Pos));
		serialize_bytes(stream, m_Blocks , sizeof(m_Blocks));
		return true;
	}

private:
	Vec2<int32_t> m_Pos = { 0,0 };
	Block m_Blocks[CHUNK_VOLUME]{};
};