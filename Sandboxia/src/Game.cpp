#include "Game.h"

GameApp::GameApp(int32_t width, int32_t height, std::string windowTitle)
{
	//LoadOptions();

	assert(!GetWindowHandle());
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	SetConfigFlags(ConfigFlags::FLAG_MSAA_4X_HINT);
	SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(ConfigFlags::FLAG_WINDOW_MAXIMIZED);
	InitWindow(width, height, windowTitle.c_str());
	InitAudioDevice();
	SetExitKey(KeyboardKey::KEY_NULL);

	Globals::Fonts::FontDefault = GetFontDefault();

	Globals::KeyboardManager = Keyboard();
	Globals::SoundManagerInstance = std::make_unique<SoundManager>(SoundManager(Globals::Options, Globals::Sounds::MainTheme));
	Globals::KeyboardManager = Keyboard();
	m_ScreenManager = std::make_unique<ScreenManager>();

	/*{
		ResPacker::Loader loader("./assets.sndrpkg");

		loader.LoadAllRaw();

		Globals::TetrisFont = loader.LoadAsFont("font", ".ttf", 28);
		Globals::TetrisFontBig = loader.LoadAsFont("font", ".ttf", 72);
		Globals::TetrisFontMedium = loader.LoadAsFont("font", ".ttf", 20);
		Globals::Animations::CellBlinkingAnimation = { loader.LoadAsTexture2D("cellblinkanim", ".png"), 15, {{0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32}, {192, 192, 32, 32}, {224, 224, 32, 32}, {256, 256, 32, 32}}, {0,0} };
		Globals::Animations::CellDisolveAnimation = { loader.LoadAsTexture2D("celldisolveanim", ".png"), 5, { {0, 0, 32, 32}, {32, 32, 32, 32}, {64, 64, 32, 32}, {96, 96, 32, 32}, {128, 128, 32, 32}, {160, 160, 32, 32} }, {0,0} };

		Globals::Sounds::MainTheme = loader.LoadAsMusicStream("themesong", ".mp3");
		Globals::Sounds::SolidifySound = loader.LoadAsSound("solidifysound", ".wav");
		Globals::Sounds::HoverSound = loader.LoadAsSound("hoversound", ".wav");
		Globals::Sounds::ClickSound = loader.LoadAsSound("clicksound", ".wav");

		Globals::Textures::SwitchOn = loader.LoadAsTexture2D("switchon", ".png");
		Globals::Textures::SwitchOff = loader.LoadAsTexture2D("switchoff", ".png");
		Globals::Textures::SliderBase = loader.LoadAsTexture2D("sliderbase", ".png");
		Globals::Textures::SliderHighlight = loader.LoadAsTexture2D("sliderhighlight", ".png");
		Globals::Textures::SliderHandle = loader.LoadAsTexture2D("sliderhandle", ".png");
		Globals::Textures::OptionsActive = loader.LoadAsTexture2D("options_normal", ".png");
		Globals::Textures::OptionsHovered = loader.LoadAsTexture2D("options_hovered", ".png");
		Globals::Textures::HotkeyFocus = loader.LoadAsTexture2D("hotkey_focus", ".png");
		Globals::Textures::HotkeyActive = loader.LoadAsTexture2D("hotkey_active", ".png");
		Globals::Textures::OptionsClicked = Globals::Textures::OptionsHovered;
		Globals::Textures::OptionsInactive = Globals::Textures::OptionsActive;
		Globals::Textures::HotkeyInactive = Globals::Textures::HotkeyActive;
		Globals::Textures::HotkeyHovered = Globals::Textures::HotkeyActive;
		Globals::Textures::HotkeyClicked = Globals::Textures::HotkeyActive;
	}*/

	//Globals::Colors::BackgroundColor = Color(20, 20, 30, 255);

	
}

GameApp::~GameApp() noexcept
{
	assert(GetWindowHandle());
	CloseAudioDevice();
	CloseWindow();
	//SaveOptions();
}

bool GameApp::GameShouldClose() const
{
	return WindowShouldClose() or States::ForceClose;
}

void GameApp::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

//void Game::LoadOptions() {
//	if (!FileExists("./settings.json")) {
//		return;
//	}
//	std::ifstream in("./settings.json");
//	nlohmann::json content = nlohmann::json::parse(in);
//	Globals::Options = content;
//}
//
//void Game::SaveOptions() {
//	nlohmann::json data = Globals::Options;
//	std::ofstream out("./settings.json");
//	out << std::setw(4) << data << std::endl;
//}

void GameApp::Update()
{
	float deltaTime = GetFrameTime();
	Globals::SoundManagerInstance->Update();
	m_ScreenManager->Update(deltaTime);
}

void GameApp::Draw()
{
	ClearBackground(Globals::Colors::BackgroundColor);
	m_ScreenManager->Draw();
}