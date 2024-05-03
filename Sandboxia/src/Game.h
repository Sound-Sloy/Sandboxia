#pragma once

#include <cstdint>
#include <cassert>
#include <string>

#include <raylib.h>

#include "Globals.h"
#include "ScreenManager.h"

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

	std::unique_ptr<ScreenManager> m_ScreenManager;
};
