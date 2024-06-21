#include "World.h"

Chunk World::GenerateChunk(Vec3<int32_t> chunkPos) {
	m_Chunks.push_back(m_Generator.GenerateChunk(chunkPos));
	return m_Chunks.back();
}

Chunk World::GetChunk(Vec3<int32_t> chunkPos) {
	for (auto& chunk : m_Chunks) {
		if (chunk.GetPos() == chunkPos) {
			return chunk;
		}
	}
	return GenerateChunk(chunkPos);
}