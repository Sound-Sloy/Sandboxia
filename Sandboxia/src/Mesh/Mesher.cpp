#include "Mesher.h"

//void Mesher::Upload(ClientChunk& chunk)
//{
//    if (!chunk.Mesh) {
//        return;
//    }
//    chunk.Mesh->vboId = (uint32_t*)calloc(Mesher::MaxChunkMeshVertexBuffers, sizeof(uint32_t));
//    chunk.Mesh->vaoId = 0;
//    chunk.Mesh->vboId[0] = 0;
//    chunk.Mesh->vboId[1] = 0;
//    chunk.Mesh->vaoId = rlLoadVertexArray();
//    rlEnableVertexArray(chunk.Mesh->vaoId);
//
//    uint32_t baseOffset = 0;
//
//    chunk.Mesh->vboId[0] = rlLoadVertexBuffer(chunk.Mesh->Vertices.data(), chunk.Mesh->VertexCount * sizeof(Vertex), false);
//    rlSetVertexAttribute(0, 3, GL_UNSIGNED_SHORT, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, Pos)));
//    rlEnableVertexAttribute(0);
//    
//    rlSetVertexAttribute(1, 1, GL_UNSIGNED_BYTE, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, Light)));
//    rlEnableVertexAttribute(1);
//    rlSetVertexAttribute(2, 1, GL_UNSIGNED_INT, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, Normal)));
//    rlEnableVertexAttribute(2);
//    rlSetVertexAttribute(3, 2, GL_UNSIGNED_SHORT, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, TexCoords)));
//    rlEnableVertexAttribute(3);
//    rlSetVertexAttribute(4, 1, GL_UNSIGNED_SHORT, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, TexIndex)));
//    rlEnableVertexAttribute(4);
//    rlSetVertexAttribute(5, 1, GL_UNSIGNED_BYTE, false, sizeof(Vertex), reinterpret_cast<void*>(baseOffset + offsetof(Vertex, AO)));
//    rlEnableVertexAttribute(5);
//
//    chunk.Mesh->vboId[1] = rlLoadVertexBufferElement(chunk.Mesh->Indices.data(), chunk.Mesh->IndexCount, false);
//    rlDisableVertexArray();
//}

void Mesher::Upload(ClientChunk& chunk) {
    chunk.Mesh->vaoId = rlLoadVertexArray();
    rlEnableVertexArray(chunk.Mesh->vaoId);

    chunk.Mesh->vboId = new uint32_t[Mesher::MaxChunkMeshVertexBuffers];  // Assuming 0 for vertex buffer, 1 for index buffer
    glGenBuffers(Mesher::MaxChunkMeshVertexBuffers, chunk.Mesh->vboId);
    chunk.Mesh->vboId[0] = rlLoadVertexBuffer(chunk.Mesh->Vertices.data(), chunk.Mesh->VertexCount * sizeof(Vertex), false);

    

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, chunk.Mesh->vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, chunk.Mesh->Vertices.size() * sizeof(Vertex), chunk.Mesh->Vertices.data(), GL_STATIC_DRAW);

    // Index Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk.Mesh->vboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk.Mesh->Indices.size() * sizeof(uint32_t), chunk.Mesh->Indices.data(), GL_STATIC_DRAW);

    // Define vertex attribute layout
    GLsizei stride = sizeof(Vertex);
    intptr_t offset = 0;

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_UNSIGNED_SHORT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    offset += sizeof(Vec3<uint16_t>);

    // LightData (assuming it is a structure, adjust appropriately)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_UNSIGNED_BYTE, GL_FALSE, stride, reinterpret_cast<void*>(offset));  // Adjust parameters based on LightData's structure
    offset += sizeof(LightData);

    // Normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, stride, reinterpret_cast<void*>(offset));
    offset += sizeof(Normal);

    // TexCoords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_UNSIGNED_SHORT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    offset += sizeof(Vec2<uint16_t>);

    // TexIndex
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_UNSIGNED_SHORT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    offset += sizeof(uint16_t);

    // AO
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_UNSIGNED_BYTE, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    offset += sizeof(uint8_t);

    glBindVertexArray(0);
}



void Mesher::Unload(ClientChunk& chunk)
{
    rlUnloadVertexArray(chunk.Mesh->vaoId);
    for (int i = 0; i < Mesher::MaxChunkMeshVertexBuffers; i++) rlUnloadVertexBuffer(chunk.Mesh->vboId[i]);

    free(chunk.Mesh->vboId);
}


void Mesher::AddFace(ChunkMesh& mesh,
    Vec3<float> v0, Vec3<float> v1, Vec3<float> v2, Vec3<float> v3,
    LightData light, Vec3<float>& normal,
    Vec2<float>& uv0, Vec2<float>& uv1, Vec2<float>& uv2, Vec2<float>& uv3,
    uint16_t textureIndex, uint8_t ambientOcclusion) {

    Normal packedNormal;
    packedNormal.PackNormal(normal.CastTo<Vector3, float>());

    mesh.Vertices.push_back(Vertex( v0.As<uint16_t>(), light, packedNormal, Vec2<uint16_t>{(uint16_t)(uv0.GetX() * 65535), (uint16_t)(uv0.GetY() * 65535)}, textureIndex, ambientOcclusion ));
    mesh.Vertices.push_back(Vertex( v1.As<uint16_t>(), light, packedNormal, Vec2<uint16_t>{(uint16_t)(uv1.GetX() * 65535), (uint16_t)(uv1.GetY() * 65535)}, textureIndex, ambientOcclusion ));
    mesh.Vertices.push_back(Vertex( v2.As<uint16_t>(), light, packedNormal, Vec2<uint16_t>{(uint16_t)(uv2.GetX() * 65535), (uint16_t)(uv2.GetY() * 65535)}, textureIndex, ambientOcclusion ));
    mesh.Vertices.push_back(Vertex( v3.As<uint16_t>(), light, packedNormal, Vec2<uint16_t>{(uint16_t)(uv3.GetX() * 65535), (uint16_t)(uv3.GetY() * 65535)}, textureIndex, ambientOcclusion ));

    uint32_t startIndex = mesh.Vertices.size() - 4;
    mesh.Indices.push_back(startIndex);
    mesh.Indices.push_back(startIndex + 1);
    mesh.Indices.push_back(startIndex + 2);
    mesh.Indices.push_back(startIndex);
    mesh.Indices.push_back(startIndex + 2);
    mesh.Indices.push_back(startIndex + 3);
}

std::shared_ptr<ChunkMesh> Mesher::MeshChunk(ClientChunk chunk) {
    Vec3<int32_t> directions[6] = {
        {1, 0, 0}, {-1, 0, 0},
        {0, 1, 0}, {0, -1, 0},
        {0, 0, 1}, {0, 0, -1}
    };

    ChunkMesh mesh;

    for (uint32_t x = 0; x < 32; ++x) {
        for (uint32_t y = 0; y < 32; ++y) {
            for (uint32_t z = 0; z < 32; ++z) {
                if (chunk.Chunk->GetBlock(Vec3{ x,y,z }.As<uint16_t>()).HasFlag(BlockFlags_e::TRANSPARENT)) {
                    continue;
                }

                for (int32_t dir = 0; dir < 6; ++dir) {
                    uint32_t nx = x + directions[dir].GetX();
                    uint32_t ny = y + directions[dir].GetY();
                    uint32_t nz = z + directions[dir].GetZ();

                    if (nx < 0 or ny < 0 or nz < 0 or 
                        nx >= 32 or ny >= 32 or nz >= 32 or 
                        chunk.Chunk->GetBlock(Vec3{ nx,ny,nz }.As<uint16_t>()).HasFlag(BlockFlags_e::TRANSPARENT))
                    {
                        //Vec3<float> v0, v1, v2, v3;
                        Vec3<uint32_t> v0, v1, v2, v3;
                        Vec3<float> normal = { 0, 0, 0 };

                        switch (dir) {
                        case 0: // +X face
                            v0 = { x + 1, y, z };
                            v1 = { x + 1, y + 1, z };
                            v2 = { x + 1, y + 1, z + 1 };
                            v3 = { x + 1, y, z + 1 };
                            normal = { 1, 0, 0 };
                            break;
                        case 1: // -X face
                            v0 = { x, y, z }; 
                            v1 = { x, y + 1, z }; 
                            v2 = { x, y + 1, z + 1 }; 
                            v3 = { x, y, z + 1 };
                            normal = { -1, 0, 0 };
                            break;
                        case 2: // +Y face
                            v0 = { x, y + 1, z }; 
                            v1 = { x + 1, y + 1, z }; 
                            v2 = { x + 1, y + 1, z + 1 }; 
                            v3 = { x, y + 1, z + 1 };
                            normal = { 0, 1, 0 };
                            break;
                        case 3: // -Y face
                            v0 = { x, y, z }; 
                            v1 = { x + 1, y, z }; 
                            v2 = { x + 1, y, z + 1 }; 
                            v3 = { x, y, z + 1 };
                            normal = { 0, -1, 0 };
                            break;
                        case 4: // +Z face
                            v0 = { x, y, z + 1 }; 
                            v1 = { x + 1, y, z + 1 }; 
                            v2 = { x + 1, y + 1, z + 1 }; 
                            v3 = { x, y + 1, z + 1 };
                            normal = { 0, 0, 1 };
                            break;
                        case 5: // -Z face
                            v0 = { x, y, z }; 
                            v1 = { x + 1, y, z }; 
                            v2 = { x + 1, y + 1, z }; 
                            v3 = { x, y + 1, z };
                            normal = { 0, 0, -1 };
                            break;
                        }

                        // Adjust positions based on actual voxel positions and calculate UVs, light, normal, and AO.
                        Vec2<float> uv0 = { 0.0f, 0.0f };
                        Vec2<float> uv1 = { 1.0f, 0.0f };
                        Vec2<float> uv2 = { 1.0f, 1.0f };
                        Vec2<float> uv3 = { 0.0f, 1.0f };

                        LightData lightData = LightData(15, 15);
                        uint16_t textureIndex = 0;  // Example texture index
                        uint8_t ambientOcclusion = 255;  // Example ambient occlusion value

                        AddFace(mesh, v0.As<float>(), v1.As<float>(), v2.As<float>(), v3.As<float>(), lightData, normal, uv0, uv1, uv2, uv3, textureIndex, ambientOcclusion);
                    }
                }
            }
        }
    }
    std::shared_ptr<ChunkMesh> meshPtr = std::make_shared<ChunkMesh>(mesh);
    m_MeshPool.push_back(meshPtr);
    return meshPtr;
}