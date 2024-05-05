#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {
	m_FnSimplex = FastNoise::New<FastNoise::Simplex>();
	m_FnFractal = FastNoise::New<FastNoise::FractalFBm>();
	m_HeightNoise = FastNoise::New<FastNoise::FractalFBm>();
	m_Noise = FastNoise::New<FastNoise::FractalFBm>();
	m_NoiseCave = FastNoise::New<FastNoise::FractalRidged>();
	m_OffsetNoise = FastNoise::New<FastNoise::FractalFBm>();
	m_RiverNoise = FastNoise::New<FastNoise::FractalFBm>();

	m_FnFractal->SetSource(m_FnSimplex);
	m_FnFractal->SetOctaveCount(5);

	m_HeightNoise->SetSource(m_FnSimplex);
	m_HeightNoise->SetLacunarity(1.f); 
	m_HeightNoise->SetOctaveCount(1);
	m_HeightNoise->SetGain(.75f);

	m_Noise->SetSource(m_FnSimplex);
	m_Noise->SetLacunarity(1.f);
	m_Noise->SetOctaveCount(3);
	m_Noise->SetGain(.75f);
	
	m_NoiseCave->SetSource(m_FnSimplex);
	m_NoiseCave->SetLacunarity(2.f);
	m_NoiseCave->SetOctaveCount(1);
	m_NoiseCave->SetGain(1.f);

	m_OffsetNoise->SetSource(m_FnSimplex);
	m_OffsetNoise->SetLacunarity(2.f);
	m_OffsetNoise->SetOctaveCount(2);
	m_OffsetNoise->SetGain(1.f);
}

Chunk WorldGenerator::GenerateChunk(Vec2<int32_t> chunkPos) {
	Chunk chunk;
	chunk.SetPos(chunkPos);
	for (uint16_t eX = 0; eX < CHUNK_SIZE_VEC3.GetX(); ++eX) {
		for (uint16_t eZ = 0; eZ < CHUNK_SIZE_VEC3.GetZ(); ++eZ) {
			for (uint16_t eY = 0; eY < CHUNK_SIZE_VEC3.GetY(); ++eY) {
				Block_e blockType = GenerateBlockInChunk(chunk, { eX,eY,eZ });

#ifndef BLOCK_CASE
#define BLOCK_CASE(BLOCKTYPE,BLOCKCLASS) { \
			case ((Block_e)BLOCKTYPE): \
			{ \
				chunk.SetBlock({ eX,eY,eZ }, BLOCKCLASS()); \
				break; \
			} \
		}
#endif
				switch (blockType)
				{
					BLOCK_CASE(Block_e::AIR, AirBlock);
					BLOCK_CASE(Block_e::STONE, StoneBlock);
					BLOCK_CASE(Block_e::DIRT, DirtBlock);
					BLOCK_CASE(Block_e::GRASS, GrassBlock);

					/*case Block_e::AIR:
					{
						chunk.SetBlock({ eX,eY,eZ }, AirBlock());
						break;
					}
					case Block_e::STONE:
					{
						chunk.SetBlock({ eX,eY,eZ }, StoneBlock());
						break;
					}
					case Block_e::DIRT:
					{
						chunk.SetBlock({ eX,eY,eZ }, DirtBlock());
						break;
					}
					case Block_e::GRASS:
					{
						chunk.SetBlock({ eX,eY,eZ }, GrassBlock());
						break;
					}*/
				default:
					break;
				}
			}
		}
	}
	return chunk;
}

Block_e WorldGenerator::GenerateBlockInChunk(Chunk& chunk, Vec3<int64_t> blockPos) {
	Block_e blockType = Block_e::AIR;

	float nsCave = m_NoiseCave->GenSingle3D(blockPos.GetX() * 1.5f, blockPos.GetY() * 1.5f, blockPos.GetZ() * 1.5f, m_Seed);
	float nsCave2 = m_NoiseCave->GenSingle3D(blockPos.GetX() * 1.5f, (blockPos.GetY() + 2048) * 1.5f, blockPos.GetZ() * 1.5f, m_Seed);

	float biomeElevation = m_HeightNoise->GenSingle2D(blockPos.GetX() * 0.05f, blockPos.GetZ() * 0.05f, m_Seed) + 1.0f;

	if (blockPos.GetY() >= 32 * biomeElevation) {
		float nsOff = m_OffsetNoise->GenSingle3D(blockPos.GetX() * 2.0f, blockPos.GetY() * 2.0f, blockPos.GetZ() * 2.0f, m_Seed) * 12.0f * (biomeElevation - 1);
		float ns = (m_Noise->GenSingle3D((blockPos.GetX() + nsOff) * 2.5f, nsOff, (blockPos.GetZ() + nsOff) * 2.5f, m_Seed) * nsOff + 1.0f) / 2.0f * 64 * biomeElevation;
		float ny = blockPos.GetY() - 32;

		float waterLevel = 60;

		if (ny < ns && nsCave * nsCave2 > 0.6f) {
			blockType = Block_e::AIR; //Caves
		}
		else if (ny + 4 < ns) {
			blockType = Block_e::STONE; //Stone
		}
		else if (ny + 1 < ns) {
			if (chunk.GetBlock(blockPos.As<uint16_t>() + Vec3<uint16_t>{0, 1, 0}).BlockType == Block_e::AIR) {
			//if (chunk->data[(index + CHUNK_SIZE_XZ) % CHUNK_SIZE] == 0) {
				blockType = Block_e::GRASS; //Grass
			}
			else {
				blockType = Block_e::DIRT; //Dirt
			}
		}
		else if (ny < ns && blockPos.GetY() < waterLevel) {
			blockType = Block_e::STONE; //Sand
		}
		// TODO: Add water. Change here. This will generate air
		else if (blockPos.GetY() < waterLevel) {
			blockType = Block_e::AIR; //Water
		}

		return blockType;
	}
	else {
		blockType = Block_e::STONE;
		if (nsCave * nsCave2 > 0.6f) blockType = Block_e::AIR; //Caves
	}
}
