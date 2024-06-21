#pragma once
#include <Server/src/CSShared.h>
#include "../Mesh/ChunkMesh.h"

class ClientChunk {
public:
	ClientChunk() {
		Chunk = nullptr;
	}
	operator bool() const {
		return Chunk != nullptr;
	}

	std::shared_ptr<Chunk> Chunk;
	std::shared_ptr<ChunkMesh> Mesh;
	bool bMeshed = false;
};