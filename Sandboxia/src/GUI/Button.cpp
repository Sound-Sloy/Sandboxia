#include "Button.h"

#pragma region Button

Button::Button(Vec2<int32_t> pos, Vec2<int32_t> size, std::string text, ButtonProperties properties)
	: m_Pos(pos), m_Size(size), m_Text(text), m_Properties(properties)
{

}

void Button::Update() {
	if (m_Properties.Font == nullptr) {
		m_DefaultFont = GetFontDefault();
		m_Properties.Font = &m_DefaultFont;
	}

	if (m_TextMeasurement == Vec2{ 0,0 }) {
		auto measurement = MeasureTextEx(*m_Properties.Font, m_Text.c_str(), m_Properties.FontSize, m_Properties.FontSpacing);
		m_TextMeasurement = { (int32_t)measurement.x, (int32_t)measurement.y };
	}

	if (m_TextPos == Vec2{ 0,0 }) {
		switch (m_Properties.TextAlignment) {
			case ButtonTextAlignment::Center: {
				m_TextPos = m_Pos + Vec2<int32_t>{(m_Size - m_TextMeasurement) / 2};
				break;
			}
			case ButtonTextAlignment::Left: {
				m_TextPos = m_Pos + Vec2<int32_t>{0, ((m_Size - m_TextMeasurement) / 2).GetY()};
				break;
			}
			case ButtonTextAlignment::Right: {
				m_TextPos = m_Pos + Vec2<int32_t>{m_Size.GetX() - m_TextMeasurement.GetX(), ((m_Size - m_TextMeasurement) / 2).GetY()};
				break;
			}
		}
	}

	if (IsClicked()) {
		if (OnClick) {
			OnClick();
		}
	}
	else if (IsHovered()) {
		if (OnHover and !m_WasHovered) {
			m_WasHovered = true;
			OnHover();
		}
	}
	else m_WasHovered = false;
}

void Button::Draw() {

	DrawRectangleRoundedLines({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BorderSize, m_Properties.BorderColor);
	//DrawRectangleRounded(, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.ForegroundColor);
	DrawRectangleRounded({ (float)m_Pos.GetX() + m_Properties.BorderSize, (float)m_Pos.GetY() + m_Properties.BorderSize, (float)m_Size.GetX() - 2 * m_Properties.BorderSize, (float)m_Size.GetY() - 2 * m_Properties.BorderSize }, m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.BackgroundColor);
	
	DrawTextEx(*m_Properties.Font, m_Text.c_str(), m_TextPos.CastAs<Vector2, float>(), m_Properties.FontSize, m_Properties.FontSpacing, m_Properties.ForegroundColor);
	if (IsClicked())
		DrawClickEffect();
	else if (IsHovered())
		DrawHoverEffect();
}

void Button::DrawHoverEffect() {
	DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, 
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.HoverColor);

}

void Button::DrawClickEffect() {
	DrawRectangleRounded({ (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, 
		m_Properties.BorderRoundness, m_Properties.BorderSegments, m_Properties.ClickColor);
}

bool Button::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	return CheckCollisionPointRec(mousePos, 
		{ (float)m_Pos.GetX(), (float)m_Pos.GetY(), 
		(float)m_Size.GetX(), (float)m_Size.GetY() });
}

bool Button::IsClicked() {
	return IsHovered() and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
}
#pragma endregion Button

#pragma region TextureButton

TextureButton::TextureButton(Vec2<int32_t> pos, Vec2<float> origin, Vec2<int32_t> size, std::string text, TextureButtonProperties properties)
	: m_Pos(pos), m_Size(size), m_Text(text), m_Properties(properties)
{
	assert(IsTextureReady(properties.ActiveTexture));
	assert(IsTextureReady(properties.InactiveTexture));
	assert(IsTextureReady(properties.ClickedTexture));
	assert(IsTextureReady(properties.HoveredTexture));

	origin *= Vec2<float>{(float)m_Properties.ActiveTexture.width, (float)m_Properties.ActiveTexture.height};
	m_Origin = Vec2<int32_t>{ (int32_t)origin.GetX(), (int32_t)origin.GetY() };
}

TextureButton::TextureButton(Vec2<int32_t> pos, Vec2<float> origin, Vec2<int32_t> size, TextureButtonProperties properties)
	: TextureButton(pos, origin, size, "", properties)
{}

void TextureButton::Update() {
	if (m_Size == Vec2{ 0, 0 }) {
		m_Size = { m_Properties.ActiveTexture.width, m_Properties.ActiveTexture.height };
	}

	if (m_Text != "") {
		if (m_Properties.Font == nullptr) {
			m_DefaultFont = GetFontDefault();
			m_Properties.Font = &m_DefaultFont;
		}

		if (m_TextMeasurement == Vec2{0, 0}) {
			auto measurement = MeasureTextEx(*m_Properties.Font, m_Text.c_str(), m_Properties.FontSize, m_Properties.FontSpacing);
			m_TextMeasurement = { (int32_t)measurement.x, (int32_t)measurement.y };
		}

		if (m_TextPos == Vec2{ 0,0 }) {
			switch (m_Properties.TextAlignment)
			{
				case ButtonTextAlignment::Center: {
					m_TextPos = m_Pos + Vec2<int32_t>{(m_Size - m_TextMeasurement) / 2};
					break;
				}
				case ButtonTextAlignment::Left: {
					m_TextPos = m_Pos + Vec2<int32_t>{0, ((m_Size - m_TextMeasurement) / 2).GetY()};
					break;
				}
				case ButtonTextAlignment::Right: {
					m_TextPos = m_Pos + Vec2<int32_t>{m_Size.GetX() - m_TextMeasurement.GetX(), ((m_Size - m_TextMeasurement) / 2).GetY()};
					break;
				}
			}
		}
	}

	if (!m_bActive) {
		return;
	}

	if (IsClicked()) {
		if (OnClick) {
			OnClick();
		}
	}
	else if (IsHovered()) {
		if (OnHover and !m_WasHovered) {
			m_WasHovered = true;
			OnHover();
		}
	}
	else m_WasHovered = false;
}

void TextureButton::Draw() {
	if (m_bActive) {
		DrawTexturePro(m_Properties.ActiveTexture, { 0,0,(float)m_Properties.ActiveTexture.width,(float)m_Properties.ActiveTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin.CastAs<Vector2, float>(), 0.f, WHITE);
	
		if (m_Text != "") {
			DrawTextEx(*m_Properties.Font, m_Text.c_str(), m_TextPos.CastAs<Vector2, float>(), m_Properties.FontSize, m_Properties.FontSpacing, m_Properties.TextColor);
		}

		if (IsClicked())
			DrawClickEffect();
		else if (IsHovered())
			DrawHoverEffect();
	}
	else {
		DrawTexturePro(m_Properties.InactiveTexture, { 0,0,(float)m_Properties.InactiveTexture.width,(float)m_Properties.InactiveTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin.CastAs<Vector2, float>(), 0.f, WHITE);

	}
}

bool TextureButton::IsActive() const {
	return m_bActive;
}

void TextureButton::SetActive(bool active) {
	m_bActive = active;
}

bool TextureButton::IsHovered() {
	Vector2 mousePos = GetMousePosition();
	return CheckCollisionPointRec(mousePos,
		{ (float)m_Pos.GetX() - (float)m_Origin.GetX(), (float)m_Pos.GetY() - (float)m_Origin.GetY(),
		(float)m_Size.GetX(), (float)m_Size.GetY() });
}

bool TextureButton::IsClicked() {
	return IsHovered() and IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
}

void TextureButton::DrawHoverEffect() {
	DrawTexturePro(m_Properties.HoveredTexture, { 0,0,(float)m_Properties.HoveredTexture.width,(float)m_Properties.HoveredTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin.CastAs<Vector2, float>(), 0.f, WHITE);
}

void TextureButton::DrawClickEffect() {
	DrawTexturePro(m_Properties.ClickedTexture, { 0,0,(float)m_Properties.ClickedTexture.width,(float)m_Properties.ClickedTexture.height }, { (float)m_Pos.GetX(), (float)m_Pos.GetY(), (float)m_Size.GetX(), (float)m_Size.GetY() }, m_Origin.CastAs<Vector2, float>(), 0.f, WHITE);
}

#pragma endregion TextureButton