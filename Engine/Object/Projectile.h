#pragma once
#include "Object/Actor.h"
#include "Engine.h"

class Projectile : public rj::Actor {
public:
	Projectile(const rj::Transform& transform, std::shared_ptr<rj::Texture> texture, float speed) : rj::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 2 };
	float speed{ 300 };
};