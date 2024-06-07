#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <unordered_map>

class Keyboard {
public:
	static Keyboard& GetInstance() {
		static Keyboard keyboard;
		return keyboard;
	}
	
	bool IsKeyPressedRepeated(KeyboardKey key);
	static KeyboardKey GetKeyPressed();
	static std::vector<KeyboardKey> GetKeysDown();

	static std::unordered_map<KeyboardKey, std::string> KeyNames;

private:
	float RepeatDelay = .11f;
	std::unordered_map<KeyboardKey, float> keyDelayMap;

};

