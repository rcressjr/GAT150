#pragma once
#include "Component.h"

namespace rj {
	class Renderer;

	class GraphicsComponent : public Component {
	public:
		virtual void Draw(Renderer* renderer) = 0;
	};
}