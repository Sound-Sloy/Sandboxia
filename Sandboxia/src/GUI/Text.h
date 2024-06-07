#pragma once
#include <iostream>
#include <raylib.h>
#include <functional>
#include <string>
#include <commons/shared/utils/Vec2.h>


class Text {
public:
	Text() = default;
	/// <summary>
	/// The constructor for Text.
	/// </summary>
	/// <param name="text">The text</param>
	/// <param name="pos">The position where the origin point will be at.</param>
	/// <param name="origin">The origin point. Values between [0.f;1.f] (.60f => 60% of text's width)</param>
	/// <param name="font"></param>
	/// <param name="fontSize"></param>
	/// <param name="fontSpacing"></param>
	/// <param name="rotation"></param>
	/// <param name="color"></param>
	Text(std::string text, Vec2<int32_t> pos, Vec2<float> origin, Font& font, float fontSize, float fontSpacing = 1.f, float rotation = 0.f, Color color = WHITE);
	Text(std::string text, Vec2<int32_t> pos, Font& font, float fontSize, float fontSpacing = 1.f, float rotation = 0.f, Color color = WHITE);
	Text(std::string text, int32_t posX, int32_t posY, float originX, float originY, Font& font, float fontSize, float fontSpacing = 1.f, float rotation = 0.f, Color color = WHITE);
	Text(std::string text, int32_t posX, int32_t posY, Font& font, float fontSize, float fontSpacing = 1.f, float rotation = 0.f, Color color = WHITE);

	void Draw();
	void DrawAt(Vec2<int32_t> pos);

	void SetText(std::string text);
	std::string GetText() const;

	Vec2<int32_t> GetSize() const;
private:
	std::string m_Text = "";

	Vec2<int32_t> m_Pos = {0,0};
	Vec2<int32_t> m_Origin = { 0,0 };
	Vec2<float> m_fOrigin = { 0.f, 0.f };

	Font m_Font = GetFontDefault();
	float m_FontSize = 0.f;
	float m_FontSpacing = 1.f;
	float m_AliveTime = 0.f;
	float m_Rotation = 0.f;
	Color m_Color = WHITE;
};