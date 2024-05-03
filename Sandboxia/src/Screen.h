#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <shared/utils/Vec2.h>

struct ScreenProperties {
	Vec2<int32_t> Size = { 0,0 };
	Vec2<int32_t> Pos = { 0,0 };
	bool Transparent = false;
	bool PassThru = false;
	bool IgnoreUpdate = false;
	bool Overlay = false;
};

class IScreen {
public:
	IScreen();
	IScreen(std::string screenName, ScreenProperties properties);

	virtual ~IScreen() = default;

	virtual void Update(float deltaTime);
	virtual void Draw();

	std::string GetName() const;
	bool IsTransparent() const;
	bool IsPassThru() const;
	bool IgnoresUpdates() const;
	bool IsOverlay() const;

private:
	static uint32_t SCREEN_COUNT;
	std::string m_Name;
	ScreenProperties m_Properties;

};
