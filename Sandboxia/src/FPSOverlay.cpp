#include "FPSOverlay.h"

FPSOverlay::FPSOverlay() :
	m_Properties(ScreenProperties{ .Size = {GetRenderWidth(), GetRenderHeight()}, .Pos = {0,0}, .IgnoreUpdate = true, .Overlay = true }),
	IScreen("##FPSOverlay", m_Properties)
{
	m_Properties.Size = { GetRenderWidth(), GetRenderHeight() };
}

void FPSOverlay::Update(float deltaTime)
{

}

void FPSOverlay::Draw()
{
	DrawText((std::to_string(GetFPS()) + " FPS / " + std::to_string(GetFrameTime()) + " ms").c_str(), 10, 10, 20, DARKGREEN);
}




