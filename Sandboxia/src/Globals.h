#pragma once
#include "SoundManager.h"
#include "ScreenManager.h"

namespace Globals {
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