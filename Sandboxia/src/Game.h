#pragma once

#include <cstdint>
#include <cassert>
#include <string>

#include <raylib.h>

#include "Globals.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include "FPSOverlay.h"

#include "Keyboard.h"

#include <Server/src/GameAdapter.h>
#include <Server/src/GameServer.h>
#include "Client/GameClient.h"
#include <thread>

#include <commons/shared/Logging/Logging.hpp>

class GameApp
{
public:
	GameApp(int32_t width, int32_t height, std::string windowTitle);

	~GameApp() noexcept;
	bool GameShouldClose() const;
	void Tick();
	//void LoadOptions();
	//void SaveOptions();

private:
	void Update();
	void Draw();

	std::thread m_ServerThread;
};
