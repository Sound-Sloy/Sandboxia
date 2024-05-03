#pragma once

#include <iostream>
#include <deque>
#include <stack>
#include "Screen.h"


class ScreenManager {
public:
	ScreenManager();

	void AddScreen(IScreen& screen);
	IScreen& GetCurrentScreen();

	void Update(float deltaTime);
	void Draw();

	ScreenManager* GetInstancePtr();

private:
	std::deque<IScreen> m_Screens;

};
