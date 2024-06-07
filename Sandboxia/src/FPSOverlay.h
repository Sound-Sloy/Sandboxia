#pragma once
#include "ScreenManager.h"

class FPSOverlay : public IScreen {
public:
	FPSOverlay();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	ScreenProperties m_Properties;
};