#pragma once
//#include "nlohmann/json.hpp"

struct Keybinds_t {
	KeyboardKey KeyLeft = KeyboardKey::KEY_A;
	KeyboardKey KeyRight = KeyboardKey::KEY_D;
	KeyboardKey KeyForward = KeyboardKey::KEY_W;
	KeyboardKey KeyBack = KeyboardKey::KEY_S;
	KeyboardKey KeyJump = KeyboardKey::KEY_SPACE;
	KeyboardKey KeySneak = KeyboardKey::KEY_LEFT_SHIFT;
	MouseButton ButtonAttack = MouseButton::MOUSE_BUTTON_LEFT;
	MouseButton ButtonUse = MouseButton::MOUSE_BUTTON_RIGHT;
};

struct Options_t {
	float MusicVolume = 1.f;
	bool MusicToggle = true;
	float SFXVolume = 1.f;
	bool SFXToggle = true;

	Keybinds_t Keybinds;
};




//inline void to_json(nlohmann::json& j, const OptionsS& p) {
//	j = nlohmann::json{ 
//		{"MusicVolume", p.MusicVolume}, 
//		{"MusicToggle", p.MusicToggle}, 
//		{"SFXVolume", p.SFXVolume}, 
//		{"SFXToggle", p.SFXToggle},
//		{"SoftDropToggle", p.SoftDropToggle},
//		{"HardDropToggle", p.HardDropToggle},
//		{"LandingPreviews", p.LandingPreviewToggle},
//		{"KeyMoveLeft", p.KeyLeft},
//		{"KeyMoveRight", p.KeyRight},
//		{"KeyRotateCW", p.KeyRotateCW},
//		{"KeyRotateCCW", p.KeyRotateCCW},
//		{"KeySoftDrop", p.KeySoftDrop},
//		{"KeyHardDrop", p.KeyHardDrop},
//		{"KeyHold", p.KeyHold}
//	};
//}
//
//inline void from_json(const nlohmann::json& j, OptionsS& p) {
//	j.at("MusicVolume").get_to(p.MusicVolume);
//	j.at("MusicToggle").get_to(p.MusicToggle);
//	j.at("SFXVolume").get_to(p.SFXVolume);
//	j.at("SFXToggle").get_to(p.SFXToggle);
//	j.at("SoftDropToggle").get_to(p.SoftDropToggle);
//	j.at("HardDropToggle").get_to(p.HardDropToggle);
//	j.at("LandingPreviews").get_to(p.LandingPreviewToggle);
//	j.at("KeyMoveLeft").get_to(p.KeyLeft);
//	j.at("KeyMoveRight").get_to(p.KeyRight);
//	j.at("KeyRotateCW").get_to(p.KeyRotateCW);
//	j.at("KeyRotateCCW").get_to(p.KeyRotateCCW);
//	j.at("KeySoftDrop").get_to(p.KeySoftDrop);
//	j.at("KeyHardDrop").get_to(p.KeyHardDrop);
//	j.at("KeyHold").get_to(p.KeyHold);
//}