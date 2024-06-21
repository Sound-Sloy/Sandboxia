#include "World3DScreen.h"

World3DScreen::World3DScreen() : 
	IScreen("##World3D", { .Size = {GetRenderWidth(), GetRenderHeight()}, .Pos = {0,0}, .Transparent = false })
{
	
}

void World3DScreen::Update(float deltaTime)
{
	if (IsKeyPressed(KeyboardKey::KEY_H)) {
		GetChunkAsync({ 0,2,0 });
	}

	for (auto& chunk : m_Chunks) {
		if (!chunk.bMeshed) {
			chunk.Mesh = GMesher.MeshChunk(chunk);
			chunk.bMeshed = true;
		}
	}
	
	UpdateCamera(&m_Camera, CameraMode::CAMERA_FIRST_PERSON);

}

void World3DScreen::Draw()
{
	rlClearScreenBuffers();

	BeginMode3D(m_Camera);
	
	for (auto& chunk : m_Chunks) {
		GRenderer.RenderChunk(chunk);
	}

	EndMode3D();
}

void World3DScreen::GetChunkAsync(Vec3<int32_t> pos) {
	GGameClientInstance->RequestChunk(Vec3(0, 0, 0));
	std::future<ClientChunk> asyncGetChunk = std::async(&GameClient::GetChunkFromQueue, GGameClientInstance);
	m_Chunks.push_back(asyncGetChunk.get());
}