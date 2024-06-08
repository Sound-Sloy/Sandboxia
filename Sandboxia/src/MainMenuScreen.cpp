#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen() : 
	IScreen("##MainMenu", { .Size = {GetRenderWidth(), GetRenderHeight()}, .Pos = {0,0}, .Transparent = false })
{
	ButtonProperties properties = {

	};
	m_ConnectButton = std::make_unique<Button>(Vec2{GetRenderWidth() / 2 - 75, GetRenderHeight() / 2 + 50}, Vec2{150,60}, "Connect", properties);

	TextBoxProperties textboxProps;
	textboxProps.FontSize = 24.f;
	textboxProps.BackgroundColor = DARKGRAY;
	textboxProps.ForegroundColor = WHITE;
	textboxProps.BorderColor = BLACK;
	textboxProps.BorderRoundness = 0.f;
	
	m_TextBox = TextBox(Vec2{ GetRenderWidth() / 2 - 150, GetRenderHeight() / 2 - 20 }, Vec2{300,40}, "Server Address", textboxProps);
}

void MainMenuScreen::Update(float deltaTime)
{
	m_ConnectButton->Update();
	m_TextBox.Update(deltaTime);
	if (IsKeyPressed(KeyboardKey::KEY_G)) {
		GGameClientInstance->RequestChunk({0,0,0});
	}
	std::shared_ptr<Chunk> chunk = GGameClientInstance->GetChunkFromQueue();
	if (chunk) {
		Logger::GetInstance().Log(LogLevel::INFO, "[Client] Chunk received");

	}
}

void MainMenuScreen::Draw()
{
	ClearBackground(Color(211, 204, 216, 255));
	DrawText("Main", 100, 100, 24, GOLD);
	m_ConnectButton->Draw();
	m_TextBox.Draw();

}
