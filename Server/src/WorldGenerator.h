#pragma once

#include <FastNoise/FastNoise.h>
#include "Chunk.h"
#include "Vec2.h"
#include "Vec3.h"

class WorldGenerator {
public:
	WorldGenerator();
	Chunk GenerateChunk(Vec2<int32_t> chunkPos);
private:
	int64_t m_Seed = 0;
	
	FastNoise::SmartNode<FastNoise::Simplex> m_FnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_FnFractal;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_HeightNoise;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_Noise;
	FastNoise::SmartNode<FastNoise::FractalRidged> m_NoiseCave;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_OffsetNoise;
	FastNoise::SmartNode<FastNoise::FractalFBm> m_RiverNoise;
	
	Block_e GenerateBlockInChunk(Chunk& chunk, Vec3<int64_t> blockPos);

};