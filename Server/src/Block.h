#pragma once

#include <cstdint>

enum class Block_e : uint16_t {
	AIR = 0,
	STONE = 1,
	DIRT = 2,
	GRASS = 3
};

typedef uint16_t BlockFlags;

enum class BlockFlags_e : BlockFlags {
	SOLID = (1 << 0),
	TRANSPARENT = (1 << 1),
	MODIFIED = (1 << 2),
	COLLIDABLE = (1 << 3),
	ALLOW_RANDOM_TICKS = (1 << 4),
	BURNABLE = (1 << 5),
	BLOCK_BREAK_PATRICLES = (1 << 6)
};

enum class BlockOrientation : uint8_t {
	NONE,
	NORTH,
	EAST,
	SOUTH,
	WEST,
	TOP,
	BOTTOM
};

class Block {
public:
	Block_e BlockType = Block_e::AIR;
	BlockFlags Flags = 0x0;
	float Hardness = 0.f;
	float Slipperiness = 0.f;
	float VelocityMultiplier = 1.f;
	float JumpVelocityMultiplier = 1.f;
	float Resistance = 0.f;
	BlockOrientation Orientation = BlockOrientation::NONE;

	bool HasFlag(BlockFlags_e flag) {
		return (bool)((uint16_t)Flags & (uint16_t)flag);
	}
	void SetFlag(BlockFlags_e flag, bool state) {
		this->Flags = state ? (uint16_t)this->Flags | (uint16_t)flag : (uint16_t)this->Flags & ~(uint16_t)(flag);
	}
};

//class Block : public Block {
//	Block_e BlockType = Block_e::AIR;
//	BlockFlags Flags = 0;
//};

class AirBlock : public Block {
public:
	AirBlock() {
		BlockType = Block_e::AIR;
		Flags = 0x0;
		Hardness = 0.f;
		Slipperiness = 0.f;
		VelocityMultiplier = 1.f;
		JumpVelocityMultiplier = 1.f;
		Resistance = 0.f;
		Orientation = BlockOrientation::NONE;
	}
};

class StoneBlock : public Block {
public:
	StoneBlock() {
		BlockType = Block_e::STONE;
		Flags = 0b1001001;
		Hardness = 1.5f;
		Slipperiness = 0.f;
		VelocityMultiplier = 1.f;
		JumpVelocityMultiplier = 1.f;
		Resistance = 6.f;
		Orientation = BlockOrientation::NONE;
	}
};

class DirtBlock : public Block {
public:
	DirtBlock() {
		BlockType = Block_e::DIRT;
		Flags = 0b1001001;
		Hardness = .5f;
		Slipperiness = 0.f;
		VelocityMultiplier = 1.f;
		JumpVelocityMultiplier = 1.f;
		Resistance = .5f;
		Orientation = BlockOrientation::NONE;
	}
};

class GrassBlock : public Block {
public:
	GrassBlock() {
		BlockType = Block_e::GRASS;
		Flags = 0b1001001;
		Hardness = .5f;
		Slipperiness = 0.f;
		VelocityMultiplier = 1.f;
		JumpVelocityMultiplier = 1.f;
		Resistance = .5f;
		Orientation = BlockOrientation::NONE;
	}
};