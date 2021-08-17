#pragma once
#include "GraphicsComponent.h"
#include <memory>

namespace rj {
	class Texture;

	class SpriteComponent : public GraphicsComponent {
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		std::shared_ptr<rj::Texture> texture;
	};
}