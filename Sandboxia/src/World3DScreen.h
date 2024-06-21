#pragma once
#include <commons/shared/Logging/Logging.hpp>
#include <queue>

#include "Server/src/CSShared.h"
#include <thread>
#include <future>

#include <vector>

#include "Client/GameClient.h"
#include "ScreenManager.h"
#include "Globals.h"
#include "Mesh/Mesher.h"
#include "Renderer/Renderer.h"


class World3DScreen : public IScreen {
public:
	World3DScreen();

	void Update(float deltaTime) override;
	void Draw() override;

	
private:
	std::vector<ClientChunk> m_Chunks;
	Camera3D m_Camera;

	void GetChunkAsync(Vec3<int32_t> pos);
};