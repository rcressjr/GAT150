#include "Actor.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include <algorithm>

namespace rj {
	
	void Actor::Update(float dt) {
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) { child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Renderer* renderer) {
		if (texture) renderer->Draw(texture, transform);
		std::for_each(children.begin(), children.end(), [renderer](auto& child) { child->Draw(renderer); });
	}

	float Actor::GetRadius() {
		return (texture) ? texture->GetSize().length() * 0.5f * transform.scale.x : 0;
	}

	void Actor::AddChild(std::unique_ptr<Actor> actor) {
		actor->parent = this;
		children.push_back(std::move(actor));
	}
}