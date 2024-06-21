#pragma once
#include <Server/src/CSShared.h>

#include "Client/GameClient.h"
#include "ScreenManager.h"
#include "Screen.h"
#include "GUI/Button.h"
#include "GUI/Text.h"
#include "GUI/TextBox.h"
#include "World3DScreen.h"

class MainMenuScreen : public IScreen {
public:
	MainMenuScreen();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	Chunk m_Chunk;
	std::unique_ptr<Button> m_ConnectButton;
	TextBox m_TextBox;

};