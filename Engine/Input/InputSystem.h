#pragma once
#include "Framework/System.h"

namespace rj {
	class InputSystem : public System {
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;
	};
}