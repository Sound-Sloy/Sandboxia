#include "Chunk.h"

Chunk::Chunk()
{
	m_Blocks.resize(CHUNK_VOLUME);
}

void Chunk::SetBlock(Vec3<uint16_t> blockPos, Block block) {
	m_Blocks[GetBlockIndexInChunk(blockPos)] = block;
}

void Chunk::SetBlockAtIndex(uint32_t index, Block block)
{
	if (index < m_Blocks.size() and index >= 0) {
		m_Blocks[index] = block;
	}
}

Block Chunk::GetBlock(Vec3<uint16_t> blockPos) const {
	//printf("[m_Blocks[%d]]\n\n\n", GetBlockIndexInChunk(blockPos));
	if (blockPos.GetX() < 32 and blockPos.GetY() < 32 and blockPos.GetZ() < 32) {
		return m_Blocks[GetBlockIndexInChunk(blockPos)];
	}
	printf("Failed Chunk::GetBlock(Vec3<uint16_t>)\n");
	return Block::FromType(Block_e::AIR);
}

Block Chunk::GetBlockByIndex(uint32_t index) const
{
	if (index < CHUNK_VOLUME and index >= 0) {
		return m_Blocks[index];
	}
}

void Chunk::SetPos(Vec3<int32_t> pos) {
	m_Pos = pos;
}


Vec3<int32_t> Chunk::GetPos() const {
	return m_Pos;
}


// Moved to header due to constexpr rules
//constexpr inline uint32_t Chunk::GetBlockIndexInChunk(Vec3<uint16_t> blockPos) {
//	return blockPos.GetX() + blockPos.GetZ() * CHUNK_SIZE_VEC3.GetZ() + blockPos.GetY() * CHUNK_SIZE_VEC3.GetY();
//}



// FIXME: yukk
// Moved to header due to constexpr rules

//constexpr inline Vec3<uint16_t> Chunk::GetBlockPosInChunk(Vec3<int64_t> blockPos) {
//	return Vec3<uint16_t> {
//		(uint16_t)(blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() >= 0 ? blockPos.GetX() % CHUNK_SIZE_VEC3.GetX() : CHUNK_SIZE_VEC3.GetX() + blockPos.GetX() % CHUNK_SIZE_VEC3.GetX()),
//		(uint16_t)(blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() >= 0 ? blockPos.GetY() % CHUNK_SIZE_VEC3.GetY() : CHUNK_SIZE_VEC3.GetY() + blockPos.GetY() % CHUNK_SIZE_VEC3.GetY()),
//		(uint16_t)(blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() >= 0 ? blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ() : CHUNK_SIZE_VEC3.GetZ() + blockPos.GetZ() % CHUNK_SIZE_VEC3.GetZ())
//	};
//}

constexpr inline Vec2<int32_t> Chunk::GetRegion() const {
	return Vec2{ m_Pos.GetX(), m_Pos.GetZ() } / REGION_SIZE_CHUNKS_AXIS;
}

Chunk::~Chunk() {
	// Clean up allocated memory
	//delete[] m_Blocks;
}