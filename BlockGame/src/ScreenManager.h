#pragma once
#include <iostream>
#include <raylib.h>
#include "States.h"
#include "ScreensEnum.h"

class ScreenManager {
public:
	ScreenManager();

	void SetScreen(ScreensE screen);
	ScreensE GetCurrentScreen() const;

	void Update(float deltaTime);
	void Draw();

	ScreenManager* GetInstance() const;

private:
	ScreensE& m_Screen = States::CurrentScreen;

	//std::unique_ptr<Board> m_Board;
	//PauseScreen m_PauseScreen;
	//OptionsScreen* m_OptionsScreen = new OptionsScreen();
	//MainScreen* m_MainScreen = new MainScreen();
	//ControlsScreen m_ControlsScreen;
};
