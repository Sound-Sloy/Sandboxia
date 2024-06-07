#pragma once

#include <iostream>
#include <FastNoise/FastNoise.h>
#include "Chunk.h"
#include <shared/utils/Vec2.h>
#include <shared/utils/Vec3.h>

class WorldGenerator {
public:
	WorldGenerator(int64_t seed = 0);
	std::shared_ptr<Chunk> GenerateChunk(Vec3<int32_t> chunkPos);
private:
	int64_t m_Seed = 0;
	
	FastNoise::SmartNode<FastNoise::Simplex> m_FnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_FnFractal;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_HeightNoise;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_Noise;
	FastNoise::SmartNode<FastNoise::FractalRidged> m_NoiseCave;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_OffsetNoise;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_RiverNoise;
	
	Block_e GenerateBlockInChunk(std::shared_ptr<const Chunk> chunk, Vec3<int64_t> blockPos);

};