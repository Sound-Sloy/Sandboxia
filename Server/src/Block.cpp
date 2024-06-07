#include "Block.h"

Block Block::FromType(Block_e blockType) {
	switch (blockType)
	{
	case Block_e::AIR:
		return AirBlock();
		break;
	case Block_e::STONE:
		return StoneBlock();

		break;
	case Block_e::DIRT:
		return DirtBlock();

		break;
	case Block_e::GRASS:
		return GrassBlock();

		break;
	default:
		break;
	}
}