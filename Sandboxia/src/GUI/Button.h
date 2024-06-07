#pragma once
#pragma warning(disable:4244)
#include <iostream>
#include <string>
#include <raylib.h>
#include <functional>
#include <assert.h>
#include <commons/shared/utils/Vec2.h>


#define ButtonEvent void

enum class ButtonTextAlignment {
	Center,
	Left,
	Right
};

struct ButtonProperties {
	ButtonTextAlignment TextAlignment = ButtonTextAlignment::Center;
	Font* Font = nullptr;
	float FontSize = 16.f;
	float FontSpacing = 1.f;

	Color ForegroundColor = WHITE;
	Color BackgroundColor = Color(0.f, 0.f, 0.f, 0.f);
	Color BorderColor = WHITE;
	Color ClickColor = Color(255.f, 255.f, 255.f, 100.f);
	Color HoverColor = Color(255.f, 255.f, 255.f, 50.f);
	int32_t BorderSize = 2;
	float BorderRoundness = 4.f;
	int32_t BorderSegments = 4;
};

struct TextureButtonProperties {
	ButtonTextAlignment TextAlignment = ButtonTextAlignment::Center;
	Font* Font = nullptr;
	float FontSize = 16.f;
	float FontSpacing = 1.f;
	Color TextColor = WHITE;

	Texture2D& ActiveTexture;
	Texture2D& InactiveTexture;
	Texture2D& HoveredTexture;
	Texture2D& ClickedTexture;
};


class Button {
public: 
	Button() = default;
	Button(Vec2<int32_t> pos, Vec2<int32_t> size, std::string text, ButtonProperties properties);
	void Update();
	void Draw();


	std::function<ButtonEvent(void)> OnClick = nullptr;
	std::function<ButtonEvent(void)> OnHover = nullptr;

private:
	ButtonProperties m_Properties;

	Vec2<int32_t> m_Pos = { 0, 0 };
	Vec2<int32_t> m_Size = { 100, 30 };
	std::string m_Text = "Click me";
	Vec2<int32_t> m_TextMeasurement = { 0,0 };
	Vec2<int32_t> m_TextPos = { 0,0 };

	Font m_DefaultFont = GetFontDefault();

	bool m_WasHovered = false;
	bool IsHovered();
	bool IsClicked();

	void DrawHoverEffect();
	void DrawClickEffect();
};

class TextureButton {
public:
	TextureButton() = default;
	/// <summary>
	/// Constructor for TextureButton
	/// </summary>
	/// <param name="pos">The position of the button</param>
	/// <param name="size">The size of the button. Leave {0,0} to use the size of the ActiveTexture.</param>
	/// <param name="origin">Values between [0.f,1.f] (.60f = 60% of the size of ActiveTexture)</param>
	/// <param name="text">Text to draw on top of all textures. Leave empty to disable text redendering.</param>
	/// <param name="properties"></param>
	TextureButton(Vec2<int32_t> pos, Vec2<float> origin, Vec2<int32_t> size, std::string text, TextureButtonProperties properties);
	TextureButton(Vec2<int32_t> pos, Vec2<float> origin, Vec2<int32_t> size, TextureButtonProperties properties);
	void Update();
	void Draw();

	bool IsActive() const;
	void SetActive(bool active = true);

	std::function<ButtonEvent(void)> OnClick = nullptr;
	std::function<ButtonEvent(void)> OnHover = nullptr;

private:
	TextureButtonProperties m_Properties;
	Vec2<int32_t> m_Pos = { 0, 0 };
	Vec2<int32_t> m_Size = { 100, 30 };
	std::string m_Text = "";
	Vec2<int32_t> m_TextMeasurement = { 0,0 };
	Vec2<int32_t> m_TextPos = { 0,0 };
	Vec2<int32_t> m_Origin = { 0,0 };
	bool m_bActive = true;

	Font m_DefaultFont = GetFontDefault();

	bool m_WasHovered = false;
	bool IsHovered();
	bool IsClicked();

	void DrawHoverEffect();
	void DrawClickEffect();
};