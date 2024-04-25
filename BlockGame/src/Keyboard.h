#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

class Keyboard {
public:
	bool IsKeyPressedRepeated(KeyboardKey key);
	static KeyboardKey GetKeyPressed();

	static std::unordered_map<KeyboardKey, std::string> KeyNames;

private:
	float RepeatDelay = .11f;
	std::unordered_map<KeyboardKey, float> keyDelayMap;

};

