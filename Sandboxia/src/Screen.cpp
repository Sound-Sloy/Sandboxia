#include "Screen.h"

#include <iostream>
uint32_t IScreen::SCREEN_COUNT = 0;

IScreen::IScreen() : 
	IScreen(std::string("noName_" + std::to_string(++SCREEN_COUNT)), ScreenProperties())
{
}

IScreen::IScreen(std::string screenName, ScreenProperties properties) : 
	m_Properties(properties)
{
	std::cout << screenName << std::endl;
	m_Name = screenName;
	if (screenName == "") {
		m_Name = "noName_" + std::to_string(++SCREEN_COUNT);
	}
	if (m_Properties.Size == Vec2{0, 0}) {
		m_Properties.Size = { GetScreenWidth(), GetScreenHeight() };
	}
}

void IScreen::Update(float deltaTime)
{

}

void IScreen::Draw()
{
	DrawRectangleV(m_Properties.Pos.CastAs<Vector2, float>(), m_Properties.Size.CastAs<Vector2, float>(), Color(255, 255, 255, 150));
	DrawTextEx(GetFontDefault(), std::string(m_Name + std::to_string(GetFPS())).c_str(), m_Properties.Pos.CastAs<Vector2, float>(), 24.f, 0.f, Color(0, 0, 0, 255));
}

std::string IScreen::GetName() const
{
	return m_Name;
}

bool IScreen::IsTransparent() const
{
	return m_Properties.Transparent;
}

bool IScreen::IsPassThru() const
{
	return m_Properties.PassThru;
}

bool IScreen::IgnoresUpdates() const
{
	return m_Properties.IgnoreUpdate;
}

bool IScreen::IsOverlay() const
{
	return m_Properties.Overlay;
}
