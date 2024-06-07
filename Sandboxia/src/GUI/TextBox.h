#pragma once
#include <raylib.h>
#include <cstdint>
#include <commons/shared/Logging/Logging.hpp>
#include <commons/shared/utils/Vec2.h>
#include <functional>
#include "../Keyboard.h"

#define TextBoxEvent void

enum class TextBoxTextAlignment {
	Center,
	Left,
	Right
};

struct TextBoxProperties {
	TextBoxTextAlignment TextAlignment = TextBoxTextAlignment::Center;
	Font* Font = nullptr;
	float FontSize = 16.f;
	float FontSpacing = 1.f;

	// Set to 0 for no char limit
	int32_t MaxChars = 128;
	Color ForegroundColor = WHITE;
	Color PlaceholderColor = LIGHTGRAY;
	Color BackgroundColor = Color(0.f, 0.f, 0.f, 0.f);
	Color BorderColor = WHITE;
	Color FocusColor = Color(255.f, 255.f, 255.f, 100.f);
	Color HoverColor = Color(255.f, 255.f, 255.f, 50.f);
	Color CursorColor = ORANGE;
	int32_t BorderSize = 2;
	float BorderRoundness = 4.f;
	int32_t BorderSegments = 4;
	Vec2<int32_t> CursorSize = { 4, 24 };
	int32_t CursorBlinkTime = 20;
};

class TextBox {
public:
	TextBox() = default;
	TextBox(Vec2<int32_t> pos, Vec2<int32_t> size, std::string placeholderText, TextBoxProperties properties);
	void Update(float deltaTime);
	void Draw();

	std::function<TextBoxEvent(void)> OnClick = nullptr;
	std::function<TextBoxEvent(void)> OnHover = nullptr;
	std::function<TextBoxEvent(void)> OnChange = nullptr;
	std::function<TextBoxEvent(bool isFocused)> OnFocusChange = nullptr;
private:
	TextBoxProperties m_Properties;
	Vec2<int32_t> m_Pos = { 0, 0 };
	Vec2<int32_t> m_Size = { 100, 30 };
	Vec2<int32_t> m_TextAreaSize = { 0,0 };
	Rectangle m_TextAreaBounds = { 0,0,0,0 };
	Rectangle m_TextboxBounds = { 0,0,0,0 };
	std::string m_PlaceholderText = "Placeholder";
	std::string m_Text = "";
	Vec2<int32_t> m_CursorPos = { 0,0 };

	static const int32_t AutoCursorCooldown = 40;
	static const int32_t AutoCursorDelay = 4;
	
	Font m_DefaultFont = GetFontDefault();
	int32_t m_AutoCursorCooldownCounter = 0;
	int32_t m_AutoCursorDelayCounter = 0;
	int32_t m_CursorIndex = 0;
	int32_t m_CursorTime = 0;
	bool m_bShowCursor = true;

	// Text index offset to start drawing in the box
	int32_t m_TextIndexOffset = 0;


	bool m_bEnabled = true;

	bool m_WasHovered = false;
	bool m_IsFocused = false;
	bool IsHovered();
	bool IsClicked();

	void DrawHoverEffect();
	void DrawClickEffect();
	void DrawCursor();
};