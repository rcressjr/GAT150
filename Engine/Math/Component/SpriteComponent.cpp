#include "SpriteComponent.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Object/Actor.h"

namespace rj {
	void SpriteComponent::Update() {

	}

	void SpriteComponent::Draw(Renderer* renderer) {
		renderer->Draw(texture, owner->transform);
	}
}