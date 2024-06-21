#pragma once
#include <iostream>
#include <raylib.h>
#include "../World/ClientChunk.h"
#include <Server/src/Block.h>
#include <commons/shared/utils/Vec3.h>
#include <commons/shared/Logging/Logging.hpp>
#include <vector>
#include <array>
#include "ChunkMesh.h"

#include <rlgl.h>
//#include <external/glfw/include/GLFW/glfw3.h>
#include <external/glad.h>

class Mesher {
public:
	Mesher() = default;
	std::shared_ptr<ChunkMesh> MeshChunk(ClientChunk chunk);
	void Upload(ClientChunk& chunk);
	void Unload(ClientChunk& chunk);
private:
	void AddFace(ChunkMesh& mesh,
		Vec3<float> v0, Vec3<float> v1, Vec3<float> v2, Vec3<float> v3,
		LightData light, Vec3<float>& normal,
		Vec2<float>& uv0, Vec2<float>& uv1, Vec2<float>& uv2, Vec2<float>& uv3,
		uint16_t textureIndex, uint8_t ambientOcclusion);

	std::vector<std::shared_ptr<ChunkMesh>> m_MeshPool;

	inline static uint32_t MaxChunkMeshVertexBuffers = 2;
};

inline Mesher GMesher;