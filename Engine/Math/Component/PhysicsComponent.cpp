#include "PhysicsComponent.h"
#include "Engine.h"

#define movement(moving) = rj::Vector2::moving

namespace rj {

	void PhysicsComponent::Update() {
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::zero;
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const {
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value) {
		JSON_READ(value, force);
		JSON_READ(value, damping);

		ApplyForce(rj::Vector2::right * force);

		return true;
	}
}