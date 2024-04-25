#pragma once
#include <iostream>
#include <raylib.h>
#include <deque>
#include "Options.h"

class SoundManager {
public:
	SoundManager() = default;
	SoundManager(Options_t& options, Music& mainMusicStream);
	void PlaySoundNow(Sound& sound);
	void PlaySoundNowUnique(Sound& sound);
	void Update();
	//SoundManager* GetInstance() const;
private:
	Options_t& m_Options;

	Music& m_MusicStream;
};