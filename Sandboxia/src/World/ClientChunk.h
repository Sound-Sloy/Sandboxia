#pragma once
#include <Server/src/CSShared.h>
#include "../Mesh/ChunkMesh.h"

class ClientChunk {
public:
	operator bool() {
		return bValid;
	}

	Chunk Chunk;
	ChunkMesh Mesh;
	bool bMeshed = false;
	bool bValid = false;
};