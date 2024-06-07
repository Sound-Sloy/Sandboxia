#include "ScreenManager.h"

ScreenManager::ScreenManager() {
	if (m_Screens.empty()) {
		m_Screens.push_front(std::make_shared<IScreen>(IScreen("##rootScr", ScreenProperties())));
	}
}

void ScreenManager::AddScreen(std::shared_ptr<IScreen> screen) {
	if (screen->IsOverlay()) {
		m_Overlays.push_front(screen);
	}
	else {
		m_Screens.push_front(screen);
	}
}

bool ScreenManager::PopScreen(std::string screenName)
{
	for (int32_t screenIndex = 0; screenIndex < m_Screens.size(); ++screenIndex) {
		if (m_Screens[screenIndex]->GetName() == screenName) {
			m_Screens.erase(m_Screens.begin() + screenIndex);
			return true;
		}
	}
	return false;
}

std::shared_ptr<IScreen> ScreenManager::GetCurrentScreen()
{
	return m_Screens.front();
}

void ScreenManager::Update(float deltaTime)
{
	int32_t noUpdateAt = -1; // -1 means there are no passthru s
	int32_t lastScreenIndex = -1;
	for (int32_t screenIndex = 0; screenIndex < m_Screens.size(); ++screenIndex) {
		if (!m_Screens[screenIndex]->IsPassThru()) {
			noUpdateAt = screenIndex;
		}
		if (!m_Screens[screenIndex]->IsTransparent()) {
			lastScreenIndex = screenIndex;
			break;
		}
	}
	if (lastScreenIndex == -1) {
		lastScreenIndex = (int32_t)m_Screens.size() - 1; // cast for no warning
	}
	if (lastScreenIndex < 0) {
		Logger::GetInstance().Log(LogLevel::WARNING, "There might be no screens for ScreenManager to manage (Update)");
		lastScreenIndex = 0;
	}

	for (int32_t screenRevIndex = lastScreenIndex; screenRevIndex >= 0; --screenRevIndex) {
		if (noUpdateAt == -1 or screenRevIndex <= noUpdateAt) {
			m_Screens[screenRevIndex]->Update(deltaTime);
		}
	}

	this->UpdateOverlays(deltaTime);

	return;

	// Delete this
	// Note: The previous algo should be this but in reverse order
	for (auto& screen : m_Screens) {
		if (!screen->IgnoresUpdates() and noUpdateAt == -1) {
			screen->Update(deltaTime);
		}
		if (!screen->IsPassThru()) {
			noUpdateAt = true;
		}
		if (!screen->IsTransparent()) {
			break;
		}
	}
}

void ScreenManager::Draw()
{
	int32_t startDrawFromIndex = (int32_t)m_Screens.size() - 1; // cast for no warning
	for (int32_t screenIndex = 0; screenIndex < m_Screens.size(); ++screenIndex) {
		if (!m_Screens[screenIndex]->IsTransparent()) {
			startDrawFromIndex = screenIndex;
			break;
		}
	}
	if (startDrawFromIndex < 0) {
		Logger::GetInstance().Log(LogLevel::WARNING, "There might be no screens for ScreenManager to manage (Draw)");
		startDrawFromIndex = 0;
	}

	for (int32_t screenIndex = startDrawFromIndex; screenIndex >= 0; --screenIndex) {
		m_Screens[screenIndex]->Draw();
	}

	this->DrawOverlays();

	return;




	// Delete this
	// Note: The previous algo should be this but in reverse order
	for (auto& screen : m_Screens) {
		screen->Draw();
		if (!screen->IsTransparent()) {
			break;
		}
	}
}

ScreenManager* ScreenManager::GetInstancePtr()
{
	return this;
}

void ScreenManager::UpdateOverlays(float deltaTime)
{
	for (auto& overlay : std::ranges::views::reverse(m_Overlays)) {
		if (overlay->IgnoresUpdates()) {
			continue;
		}
		overlay->Update(deltaTime);
	}
}

void ScreenManager::DrawOverlays()
{
	for (auto& overlay : std::ranges::views::reverse(m_Overlays)) {
		overlay->Draw();
	}
}



