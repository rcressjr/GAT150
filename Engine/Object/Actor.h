#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include <vector>
#include <memory>

namespace rj {
	class Scene;

	class Actor : public Object {
	public:
		Actor() {}
		Actor(const Transform& transform) : transform{ transform } {}

		virtual void Update(float dt);
		virtual void Draw();

		virtual void OnCollision(Actor* actor) {}
		void AddChild(std::unique_ptr<Actor> actor);
		virtual void Initialize() {}

		float GetRadius();

	public:
		bool destroy{ false };
		Transform transform;
		Scene* scene{ nullptr };
		std::string tag;

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;
	};
}