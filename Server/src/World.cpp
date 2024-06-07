#include "World.h"

std::shared_ptr<Chunk> World::GenerateChunk(Vec3<int32_t> chunkPos) {
	m_Chunks.push_back(m_Generator.GenerateChunk(chunkPos));
	return m_Chunks.back();
}

std::shared_ptr<Chunk> World::GetChunkPtr(Vec3<int32_t> chunkPos) {
	for (auto& chunkPtr : m_Chunks) {
		if (chunkPtr->GetPos() == chunkPos) {
			return chunkPtr;
		}
	}
	return GenerateChunk(chunkPos);
}