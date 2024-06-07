#pragma once
#include <yojimbo.h>
#include "Block.h"

class CompressedBlock {
public:
	Block_e BlockType = Block_e::AIR;
	LightData Light = { 0,0 };
	BlockOrientation Orientation = BlockOrientation::NONE;

	void FromBlock(Block block) {
		BlockType = block.BlockType;
		Light = block.Light;
		Orientation = block.Orientation;
	}

	Block ToBlock() {
		Block block = Block::FromType(BlockType);
		block.Light = Light;
		block.Orientation = Orientation;
		return block;
	}

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bytes(stream, (uint8_t*)&BlockType, sizeof(BlockType));
		serialize_bytes(stream, (uint8_t*)&Light, sizeof(Light));
		serialize_bytes(stream, (uint8_t*)&Orientation, sizeof(Orientation));
		return true;
	}
};