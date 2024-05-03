#include "Text.h"

Text::Text(std::string text, Vec2<int32_t> pos, Vec2<float> origin, Font& font, float fontSize, float fontSpacing, float rotation, Color color)
	: m_Text(text), m_Pos(pos), m_Font(font), m_FontSize(fontSize), m_FontSpacing(fontSpacing), m_Rotation(rotation), m_Color(color)
{
	m_fOrigin = origin;
	Vector2 textmeasurement = MeasureTextEx(font, text.c_str(), fontSize, fontSpacing);
	m_Origin = { (int32_t)(origin.GetX() * textmeasurement.x), (int32_t)(origin.GetY() * textmeasurement.y) };
}


Text::Text(std::string text, Vec2<int32_t> pos, Font& font, float fontSize, float fontSpacing, float rotation, Color color) 
	: Text(text, pos, {0.f,0.f}, font, fontSize, fontSpacing, rotation, color)
{}

Text::Text(std::string text, int32_t posX, int32_t posY, float originX, float originY, Font& font, float fontSize, float fontSpacing, float rotation, Color color)
	: Text(text, { posX, posY }, {originX, originY}, font, fontSize, fontSpacing, rotation, color)
{}

Text::Text(std::string text, int32_t posX, int32_t posY, Font& font, float fontSize, float fontSpacing, float rotation, Color color)
	: Text(text, { posX, posY }, { 0.f, 0.f }, font, fontSize, fontSpacing, rotation, color)
{}


void Text::Draw() {
	DrawAt(m_Pos);
}

void Text::DrawAt(Vec2<int32_t> pos) {
	DrawTextPro(m_Font, m_Text.c_str(), { (float)pos.GetX(), (float)pos.GetY() }, { (float)m_Origin.GetX(), (float)m_Origin.GetY() }, m_Rotation, m_FontSize, m_FontSpacing, m_Color);
}

void Text::SetText(std::string text) {
	m_Text = text;
	Vector2 textmeasurement = MeasureTextEx(m_Font, text.c_str(), m_FontSize, m_FontSpacing);
	m_Origin = { (int32_t)(m_fOrigin.GetX() * textmeasurement.x), (int32_t)(m_fOrigin.GetY() * textmeasurement.y) };

}

std::string Text::GetText() const {
	return m_Text;
}

Vec2<int32_t> Text::GetSize() const
{
	Vector2 textmsrmt = MeasureTextEx(m_Font, m_Text.c_str(), m_FontSize, m_FontSpacing);
	return Vec2{ (int32_t)textmsrmt.x, (int32_t)textmsrmt.y };
}
