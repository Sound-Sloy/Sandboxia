#pragma once

#include <iostream>
#include <deque>
#include <stack>
#include <commons/shared/Logging/Logging.hpp>
#include "Screen.h"

class ScreenManager {
public:
	ScreenManager();

	void AddScreen(std::shared_ptr<IScreen> screen);
	
	/// <summary>
	/// Removes the first screen found with a name.
	/// </summary>
	/// <param name="screenName"></param>
	/// <returns>
	/// true  -> if a screen was removed
	/// false -> if no screen was removed
	/// </returns>
	bool PopScreen(std::string screenName);

	std::shared_ptr<IScreen> GetCurrentScreen();

	void Update(float deltaTime);
	void Draw();

	ScreenManager* GetInstancePtr();

private:
	std::deque<std::shared_ptr<IScreen>> m_Screens;
	std::deque<std::shared_ptr<IScreen>> m_Overlays;

	void UpdateOverlays(float deltaTime);
	void DrawOverlays();
};

inline ScreenManager GScreenManagerInstance;