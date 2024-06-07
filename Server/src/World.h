#pragma once
#include <iostream>
#include <vector>
#include "WorldGenerator.h"
#include <shared/utils/Vec3.h>

class World {
public:
	World() = default;

	std::shared_ptr<Chunk> GenerateChunk(Vec3<int32_t> chunkPos);
	std::shared_ptr<Chunk> GetChunkPtr(Vec3<int32_t> chunkPos);
private:
	std::vector<std::shared_ptr<Chunk>> m_Chunks;

	WorldGenerator m_Generator;
};