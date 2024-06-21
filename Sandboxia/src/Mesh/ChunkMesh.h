#pragma once
#include <vector>
#include <commons/shared/utils/Vec2.h>
#include <commons/shared/utils/Vec3.h>
#include <commons/shared/Logging/Logging.hpp>
#include <Server/src/Block.h>
#include <raylib.h>


struct Normal {
public:
	void PackNormal(Vector3 normal) {
		uint32_t x = (uint32_t)((normal.x + 1.0f) * 511.5f);
		uint32_t y = (uint32_t)((normal.y + 1.0f) * 511.5f);
		uint32_t z = (uint32_t)((normal.z + 1.0f) * 511.5f);

		Normal = (x << 20) | (y << 10) | z;
	}

	Vector3 UnpackNormal() {
		Vector3 normal;
		normal.x = ((Normal >> 20) & 0x3FF) / 511.5f - 1.0f;
		normal.y = ((Normal >> 10) & 0x3FF) / 511.5f - 1.0f;
		normal.z = (Normal & 0x3FF) / 511.5f - 1.0f;
		return normal;
	}


	uint32_t Normal;
};

struct Vertex {
public:
	Vertex(Vec3<uint16_t> pos, LightData light, Normal normal, Vec2<uint16_t> texCoords, 
		uint16_t texIndex, uint8_t ao) : 
		Pos(pos), Light(light), Normal(normal), TexCoords(texCoords), TexIndex(texIndex), AO(ao)
	{};

	Vec3<uint16_t> Pos;
	LightData Light;
	Normal Normal;
	Vec2<uint16_t> TexCoords;
	uint16_t TexIndex;
	uint8_t AO;  // Ambient occlusion value (0-255)
};

struct ChunkMesh {
	std::vector<Vertex> Vertices;
	std::vector<uint32_t> Indices;
	int32_t VertexCount;
	int32_t IndexCount;

	// OpenGL identifiers
	uint32_t vaoId;     // OpenGL Vertex Array Object id
	uint32_t* vboId;    // OpenGL Vertex Buffer Objects id (default vertex data)
};