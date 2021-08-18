#pragma once
#include "Math/Component/SpriteComponent.h"
#include <SDL.h>

namespace rj {

	class SpriteAnimationComponent : public SpriteComponent {
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		int frame = 0;
		int fps = 0;
		int numFramesX = 0;
		int	numFramesY = 0;
		float frameTime = 0;
		float frameTimer = 0;
		SDL_Rect rect;
	};
}