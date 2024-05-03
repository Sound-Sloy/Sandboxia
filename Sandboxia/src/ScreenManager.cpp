#include "ScreenManager.h"

ScreenManager::ScreenManager() {
	if (m_Screens.empty()) {
		m_Screens.push_front(IScreen("rootScr", ScreenProperties()));
	}
}

void ScreenManager::AddScreen(IScreen& screen) {
	m_Screens.push_front(screen);
}

IScreen& ScreenManager::GetCurrentScreen()
{
	return m_Screens.front();
}

void ScreenManager::Update(float deltaTime)
{
	int32_t noUpdateAt = -1; // -1 means there are no passthru s
	int32_t lastScreenIndex = -1;
	for (int32_t screenIndex = 0; screenIndex < m_Screens.size(); ++screenIndex) {
		if (!m_Screens[screenIndex].IsPassThru()) {
			noUpdateAt = screenIndex;
		}
		if (!m_Screens[screenIndex].IsTransparent()) {
			lastScreenIndex = screenIndex;
			break;
		}
	}
	if (lastScreenIndex == -1) {
		lastScreenIndex = m_Screens.size() - 1;
	}
	if (lastScreenIndex < 0) {
		std::cout << "[WARNING] There might be no screens for ScreenManager to manage" << std::endl;
		lastScreenIndex = 0;
	}

	for (int32_t screenRevIndex = lastScreenIndex; screenRevIndex >= 0; --screenRevIndex) {
		if (noUpdateAt == -1 or screenRevIndex <= noUpdateAt) {
			m_Screens[screenRevIndex].Update(deltaTime);
		}
	}
	return;

	// Delete this
	// Note: The previous algo should be this but in reverse order
	for (auto& screen : m_Screens) {
		if (!screen.IgnoresUpdates() and noUpdateAt == -1) {
			screen.Update(deltaTime);
		}
		if (!screen.IsPassThru()) {
			noUpdateAt = true;
		}
		if (!screen.IsTransparent()) {
			break;
		}
	}
}

void ScreenManager::Draw()
{
	for (auto& screen : m_Screens) {
		screen.Draw();
		if (!screen.IsTransparent()) {
			break;
		}
	}
}

ScreenManager* ScreenManager::GetInstancePtr()
{
	return this;
}



