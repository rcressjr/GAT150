#include "Actor.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Math/Component/Component.h"
#include "Math/Component/GraphicsComponent.h"
#include <algorithm>

namespace rj {
	
	void Actor::Update(float dt) {
		std::for_each(components.begin(), components.end(), [](auto& component) { component->Update(); });

		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) { child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Renderer* renderer) {
		std::for_each(components.begin(), components.end(), [renderer](auto& component) {  if (dynamic_cast<GraphicsComponent*>(component.get())) { dynamic_cast<GraphicsComponent*>(component.get())->Draw(renderer); }});

		std::for_each(children.begin(), children.end(), [renderer](auto& child) { child->Draw(renderer); });
	}

	float Actor::GetRadius() {
		return 0;
	}

	void Actor::AddChild(std::unique_ptr<Actor> actor) {
		actor->parent = this;
		children.push_back(std::move(actor));
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->owner = this;
		components.push_back(std::move(component));
	}
}