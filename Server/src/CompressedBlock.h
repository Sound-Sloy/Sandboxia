#pragma once
#include <yojimbo.h>
#include "Block.h"

class CompressedBlock {
public:
	Block_e BlockType = Block_e::AIR;
	BlockOrientation Orientation = BlockOrientation::NONE;

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, BlockType, sizeof(BlockType));
		serialize_bytes(stream, Orientation, sizeof(Orientation));
		return true;
	}
};