#pragma once
#include "ScreensEnum.h"

namespace States {
	inline bool ForceClose = false;
	inline ScreensE CurrentScreen = ScreensE::None;
	inline ScreensE LastScreen = ScreensE::None;

	inline static void ChangeScreen(ScreensE screen) {
		LastScreen = CurrentScreen;
		CurrentScreen = screen;
	}

	namespace Flags {
		inline bool ForceResetBoard = false;
	}
}