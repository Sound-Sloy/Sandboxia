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
	Chunk();
	virtual ~Chunk();
	void SetBlock(Vec3<uint16_t> blockPos, Block block);
	void SetBlockAtIndex(uint32_t index, Block block);
	Block GetBlock(Vec3<uint16_t> blockPos) const;
	Block GetBlockByIndex(uint32_t index) const;

	void SetPos(Vec3<int32_t> pos);
	Vec3<int32_t> GetPos() const;

	constexpr inline static uint32_t GetBlockIndexInChunk(Vec3<uint16_t> blockPos) {
		return blockPos.GetX() + blockPos.GetZ() * CHUNK_SIZE_VEC3.GetZ() + blockPos.GetY() * CHUNK_SIZE_VEC3.GetY();
	}
	constexpr inline static Vec3<uint16_t> GetBlockPosInChunk(Vec3<int64_t> blockPos) {
		return Vec3<uint16_t> {
				(uint16_t)(blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() >= 0 ? blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() : CHUNK_SIZE_VEC3.GetX() + blockPos.GetX() % CHUNK_SIZE_VEC3.GetX()),
				(uint16_t)(blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() >= 0 ? blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() : CHUNK_SIZE_VEC3.GetY() + blockPos.GetY() % CHUNK_SIZE_VEC3.GetY()),
				(uint16_t)(blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() >= 0 ? blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() : CHUNK_SIZE_VEC3.GetZ() + blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ())
		};
	}

	constexpr inline Vec2<int32_t> GetRegion() const;

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, m_Pos, sizeof(m_Pos));
		serialize_bytes(stream, m_Blocks , sizeof(CHUNK_VOLUME * sizeof(Block)));
		return true;
	}

private:
	Vec3<int32_t> m_Pos = { 0,0,0 };
	//Block* m_Blocks = nullptr;
	Block m_Blocks[CHUNK_VOLUME];
};