#pragma once
#include <commons/shared/Logging/Logging.hpp>
#include "ScreenManager.h"
#include "Globals.h"

class World3DScreem : public IScreen {
public:
	World3DScreem();

	void Update(float deltaTime) override;
	void Draw() override;
private:
};