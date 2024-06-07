#include "Chunk.h"

void Chunk::SetBlock(Vec3<uint16_t> blockPos, Block block) {
	m_Blocks[GetBlockIndexInChunk(blockPos)] = block;
}

void Chunk::SetBlockAtIndex(uint32_t index, Block block)
{
	if (index < sizeof(m_Blocks)) {
		m_Blocks[index] = block;
	}
}

Block Chunk::GetBlock(Vec3<uint16_t> blockPos) const {
	return m_Blocks[GetBlockIndexInChunk(blockPos)];
}

Block Chunk::GetBlockByIndex(uint32_t index) const
{
	if (index < sizeof(m_Blocks)) {
		return m_Blocks[index];
	}
}

void Chunk::SetPos(Vec3<int32_t> pos) {
	m_Pos = pos;
}


Vec3<int32_t> Chunk::GetPos() const {
	return m_Pos;
}

constexpr uint32_t Chunk::GetBlockIndexInChunk(Vec3<uint16_t> blockPos) {
	return blockPos.GetX() + blockPos.GetZ() * CHUNK_SIZE_VEC3.GetZ() + blockPos.GetY() * CHUNK_SIZE_VEC3.GetY();
}


// FIXME: yukk
constexpr Vec3<uint16_t> Chunk::GetBlockPosInChunk(Vec3<int64_t> blockPos) {
	return Vec3<uint16_t> {
		(uint16_t)(blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() >= 0 ? blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() : CHUNK_SIZE_VEC3.GetX() + blockPos.GetX() % CHUNK_SIZE_VEC3.GetX()),
		(uint16_t)(blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() >= 0 ? blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() : CHUNK_SIZE_VEC3.GetY() + blockPos.GetY() % CHUNK_SIZE_VEC3.GetY()),
		(uint16_t)(blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() >= 0 ? blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() : CHUNK_SIZE_VEC3.GetZ() + blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ())
	};
}

constexpr inline Vec2<int32_t> Chunk::GetRegion() const {
	return Vec2{ m_Pos.GetX(), m_Pos.GetZ() } / REGION_SIZE_CHUNKS_AXIS;
}