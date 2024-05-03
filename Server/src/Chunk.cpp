#include "Chunk.h"

void Chunk::SetBlock(Vec3<uint16_t> blockPos, Block block) {
	m_Blocks[GetBlockIndexInChunk(blockPos)] = block;
}

Block Chunk::GetBlock(Vec3<uint16_t> blockPos) const {
	return m_Blocks[GetBlockIndexInChunk(blockPos)];
}

void Chunk::SetPos(Vec2<int32_t> pos) {
	m_Pos = pos;
}

Vec2<int32_t> Chunk::GetPos() const {
	return m_Pos;
}

constexpr uint32_t Chunk::GetBlockIndexInChunk(Vec3<uint16_t> blockPos) {
	return blockPos.GetX() + blockPos.GetZ() * CHUNK_SIZE_VEC3.GetZ() + blockPos.GetY() * CHUNK_SIZE_VEC3.GetY();
}

// FIXME: yukk
constexpr Vec3<uint16_t> GetBlockPosInChunk(Vec3<int64_t> blockPos) {
	return Vec3<uint16_t> {
		blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() >= 0 ? blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() : CHUNK_SIZE_VEC3.GetX() + blockPos.GetX() % CHUNK_SIZE_VEC3.GetX(),
		blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() >= 0 ? blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() : CHUNK_SIZE_VEC3.GetY() + blockPos.GetY() % CHUNK_SIZE_VEC3.GetY(),
		blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() >= 0 ? blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() : CHUNK_SIZE_VEC3.GetZ() + blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ()

	};
}

constexpr inline Vec2<int32_t> Chunk::GetRegion() const {
	return m_Pos / REGION_SIZE_CHUNKS_AXIS;
}