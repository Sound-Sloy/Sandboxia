#pragma once
#include "Keyboard.h"
#include "SoundManager.h"

namespace Globals {
	inline Keyboard KeyboardManager;
	inline std::unique_ptr<SoundManager> SoundManagerInstance;
	inline Options_t Options;

	namespace Fonts {
		inline Font FontDefault;
	}

	namespace Textures {

	}

	namespace Sounds {
		inline Music MainTheme;
	}

	namespace Colors {
		inline Color BackgroundColor = LIGHTGRAY;
	}
}