#include "PickupComponent.h"
#include "Engine.h"
#include <memory>

using namespace rj;

PickupComponent::~PickupComponent() {
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PickupComponent::Create() {
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickupComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("gotcoin", "audio/coin.wav");
}

void PickupComponent::Update() {

}

void PickupComponent::OnCollisionEnter(const rj::Event& event) {
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "player")) owner->scene->engine->Get<AudioSystem>()->PlayAudio("gotcoin");
	else return;
}

void PickupComponent::OnCollisionExit(const rj::Event& event) {
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "player")) {
		//owner->scene->RemoveActor(this->owner);
		//this->~PickupComponent();
		owner->destroy = true;
	}
	else return;
}

bool PickupComponent::Write(const rapidjson::Value& value) const {
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value) {
	JSON_READ(value, coins)

	return true;
}
