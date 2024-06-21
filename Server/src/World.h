#pragma once
#include <iostream>
#include <vector>
#include "WorldGenerator.h"
#include <shared/utils/Vec3.h>

class World {
public:
	World() = default;

	Chunk GenerateChunk(Vec3<int32_t> chunkPos);
	Chunk GetChunk(Vec3<int32_t> chunkPos);
private:
	std::vector<Chunk> m_Chunks;

	WorldGenerator m_Generator;
};