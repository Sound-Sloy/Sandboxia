#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
	
}

void ScreenManager::SetScreen(ScreensE screen) {
	m_Screen = screen;
}

ScreensE ScreenManager::GetCurrentScreen() const {
	return m_Screen;
}

void ScreenManager::Update(float deltaTime) {
	//if (IsKeyPressed(KeyboardKey::KEY_ESCAPE)) {
	//	if (m_Screen == ScreensE::Board) {
	//		m_Screen = ScreensE::Pause;
	//		//m_PauseScreen.SetActive(true);
	//	}
	//	else if (m_Screen == ScreensE::Pause) {
	//		m_Screen = ScreensE::Board;
	//		//m_PauseScreen.SetActive(false);
	//	}
	//}

	//if (m_PauseScreen.FlagShouldRestartBoard or States::Flags::ForceResetBoard) {
	//	m_Board = std::make_unique<Board>(Vec2{ 100,50 }, Vec2{ 10,20 });
	//	m_PauseScreen.FlagShouldRestartBoard = false;
	//	States::Flags::ForceResetBoard = false;
	//}

	switch (m_Screen)
	{
		/*case ScreensE::Board: {
			m_Board->Update(deltaTime);
			m_PauseScreen.SetActive(false);
			break;
		}
		case ScreensE::Pause: {
			m_PauseScreen.SetActive(true);
			m_PauseScreen.Update();
			break;
		}
		case ScreensE::Main: {
			m_PauseScreen.SetActive(false);
			m_MainScreen->Update();
			break;
		}
		case ScreensE::Options: {
			m_OptionsScreen->Update();
			m_PauseScreen.SetActive(false);
			break;
		}
		case ScreensE::Controls: {
			m_ControlsScreen.Update();
			break;
		}*/
	}
}

void ScreenManager::Draw() {
	switch (m_Screen)
	{
		/*case ScreensE::Board: {
			m_Board->Draw();
			break;
		}
		case ScreensE::Pause: {
			m_PauseScreen.Draw();
			break;
		}
		case ScreensE::Main: {
			m_MainScreen->Draw();
			break;
		}
		case ScreensE::Options: {
			m_OptionsScreen->Draw();
			break;
		}
		case ScreensE::Controls: {
			m_ControlsScreen.Draw();
			break;
		}*/
	}
}

ScreenManager* ScreenManager::GetInstance() const {
	return (ScreenManager*)this;
}