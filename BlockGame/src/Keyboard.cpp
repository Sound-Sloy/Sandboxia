#include "Keyboard.h"

bool Keyboard::IsKeyPressedRepeated(KeyboardKey key) {
	if (!IsKeyDown(key)) {
		return false;
	}
	if (!this->keyDelayMap.contains(key)) {
		this->keyDelayMap[key] = 0.f;
	}
	if (GetTime()-this->keyDelayMap[key] < this->RepeatDelay) {
		return false;
	}
	this->keyDelayMap[key] = (float)GetTime();
	return true;
}

KeyboardKey Keyboard::GetKeyPressed()
{
	for (int32_t _ = 0; _ < 512; ++_) {
		if (IsKeyPressed(_)) {
			return (KeyboardKey)_;
		}
	}
	return KeyboardKey::KEY_NULL;
}

std::unordered_map<KeyboardKey, std::string> Keyboard::KeyNames = {
        {KeyboardKey::KEY_NULL , "None"},
        {KeyboardKey::KEY_APOSTROPHE , "'"},
        {KeyboardKey::KEY_COMMA , ","},
        {KeyboardKey::KEY_MINUS , "-"},
        {KeyboardKey::KEY_PERIOD , "."},
        {KeyboardKey::KEY_SLASH , "/"},
        {KeyboardKey::KEY_ZERO , "0"},
        {KeyboardKey::KEY_ONE , "1"},
        {KeyboardKey::KEY_TWO , "2"},
        {KeyboardKey::KEY_THREE , "3"},
        {KeyboardKey::KEY_FOUR , "4"},
        {KeyboardKey::KEY_FIVE , "5"},
        {KeyboardKey::KEY_SIX , "6"},
        {KeyboardKey::KEY_SEVEN , "7"},
        {KeyboardKey::KEY_EIGHT , "8"},
        {KeyboardKey::KEY_NINE , "9"},
        {KeyboardKey::KEY_SEMICOLON , ";"},
        {KeyboardKey::KEY_EQUAL , "="},
        {KeyboardKey::KEY_A , "A"},
        {KeyboardKey::KEY_B , "B"},
        {KeyboardKey::KEY_C , "C"},
        {KeyboardKey::KEY_D , "D"},
        {KeyboardKey::KEY_E , "E"},
        {KeyboardKey::KEY_F , "F"},
        {KeyboardKey::KEY_G , "G"},
        {KeyboardKey::KEY_H , "H"},
        {KeyboardKey::KEY_I , "I"},
        {KeyboardKey::KEY_J , "J"},
        {KeyboardKey::KEY_K , "K"},
        {KeyboardKey::KEY_L , "L"},
        {KeyboardKey::KEY_M , "M"},
        {KeyboardKey::KEY_N , "N"},
        {KeyboardKey::KEY_O , "O"},
        {KeyboardKey::KEY_P , "P"},
        {KeyboardKey::KEY_Q , "Q"},
        {KeyboardKey::KEY_R , "R"},
        {KeyboardKey::KEY_S , "S"},
        {KeyboardKey::KEY_T , "T"},
        {KeyboardKey::KEY_U , "U"},
        {KeyboardKey::KEY_V , "V"},
        {KeyboardKey::KEY_W , "W"},
        {KeyboardKey::KEY_X , "X"},
        {KeyboardKey::KEY_Y , "Y"},
        {KeyboardKey::KEY_Z , "Z"},
        {KeyboardKey::KEY_LEFT_BRACKET , "["},
        {KeyboardKey::KEY_BACKSLASH , "\\"},
        {KeyboardKey::KEY_RIGHT_BRACKET , "]"},
        {KeyboardKey::KEY_GRAVE , "`"},
        {KeyboardKey::KEY_SPACE , "Space"},
        {KeyboardKey::KEY_ESCAPE , "Esc"},
        {KeyboardKey::KEY_ENTER , "Enter"},
        {KeyboardKey::KEY_TAB , "Tab"},
        {KeyboardKey::KEY_BACKSPACE , "Backspace"},
        {KeyboardKey::KEY_INSERT , "Ins"},
        {KeyboardKey::KEY_DELETE , "Del"},
        {KeyboardKey::KEY_RIGHT , "Right"},
        {KeyboardKey::KEY_LEFT , "Left"},
        {KeyboardKey::KEY_DOWN , "Down"},
        {KeyboardKey::KEY_UP , "Up"},
        {KeyboardKey::KEY_PAGE_UP , "Page up"},
        {KeyboardKey::KEY_PAGE_DOWN , "Page down"},
        {KeyboardKey::KEY_HOME , "Home"},
        {KeyboardKey::KEY_END , "End"},
        {KeyboardKey::KEY_CAPS_LOCK , "Caps lock"},
        {KeyboardKey::KEY_SCROLL_LOCK , "Scroll down"},
        {KeyboardKey::KEY_NUM_LOCK , "Num lock"},
        {KeyboardKey::KEY_PRINT_SCREEN , "Print screen"},
        {KeyboardKey::KEY_PAUSE , "Pause"},
        {KeyboardKey::KEY_F1 , "F1"},
        {KeyboardKey::KEY_F2 , "F2"},
        {KeyboardKey::KEY_F3 , "F3"},
        {KeyboardKey::KEY_F4 , "F4"},
        {KeyboardKey::KEY_F5 , "F5"},
        {KeyboardKey::KEY_F6 , "F6"},
        {KeyboardKey::KEY_F7 , "F7"},
        {KeyboardKey::KEY_F8 , "F8"},
        {KeyboardKey::KEY_F9 , "F9"},
        {KeyboardKey::KEY_F10 , "F10"},
        {KeyboardKey::KEY_F11 , "F11"},
        {KeyboardKey::KEY_F12 , "F12"},
        {KeyboardKey::KEY_LEFT_SHIFT , "L Shift"},
        {KeyboardKey::KEY_LEFT_CONTROL , "L Control"},
        {KeyboardKey::KEY_LEFT_ALT , "L Alt"},
        {KeyboardKey::KEY_LEFT_SUPER , "Super left"},
        {KeyboardKey::KEY_RIGHT_SHIFT , "R Shift"},
        {KeyboardKey::KEY_RIGHT_CONTROL , "R Control"},
        {KeyboardKey::KEY_RIGHT_ALT , "R Alt"},
        {KeyboardKey::KEY_RIGHT_SUPER , "Super right"},
        {KeyboardKey::KEY_KB_MENU , "Menu"},
        {KeyboardKey::KEY_KP_0 , "Keypad 0"},
        {KeyboardKey::KEY_KP_1 , "Keypad 1"},
        {KeyboardKey::KEY_KP_2 , "Keypad 2"},
        {KeyboardKey::KEY_KP_3 , "Keypad 3"},
        {KeyboardKey::KEY_KP_4 , "Keypad 4"},
        {KeyboardKey::KEY_KP_5 , "Keypad 5"},
        {KeyboardKey::KEY_KP_6 , "Keypad 6"},
        {KeyboardKey::KEY_KP_7 , "Keypad 7"},
        {KeyboardKey::KEY_KP_8 , "Keypad 8"},
        {KeyboardKey::KEY_KP_9 , "Keypad 9"},
        {KeyboardKey::KEY_KP_DECIMAL , "Keypad ."},
        {KeyboardKey::KEY_KP_DIVIDE , "Keypad /"},
        {KeyboardKey::KEY_KP_MULTIPLY , "Keypad *"},
        {KeyboardKey::KEY_KP_SUBTRACT , "Keypad -"},
        {KeyboardKey::KEY_KP_ADD , "Keypad +"},
        {KeyboardKey::KEY_KP_ENTER , "Keypad Enter"},
        {KeyboardKey::KEY_KP_EQUAL , "Keypad ="},
        {KeyboardKey::KEY_BACK , "Android back button"},
        {KeyboardKey::KEY_MENU , "Android menu button"},
        {KeyboardKey::KEY_VOLUME_UP , "Android volume up button"},
        {KeyboardKey::KEY_VOLUME_DOWN, "Android volume down button"}
};