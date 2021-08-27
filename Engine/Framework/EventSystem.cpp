#include "EventSystem.h"
#include "Object/Object.h"

void rj::EventSystem::Startup() {

}

void rj::EventSystem::Shutdown() {

}

void rj::EventSystem::Update(float dt) {

}

void rj::EventSystem::Subscribe(const std::string& name, function_t function, Object* receiver) {
	Observer observer;
	observer.function = function;
	observer.reciever = receiver;

	observers[name].push_back(observer);
}

void rj::EventSystem::Notify(const Event& event) { 
	auto& eventObservers = observers[event.name];
	for (auto& observer : eventObservers) {
		if (event.receiver == nullptr || event.receiver == observer.reciever) {
			observer.function(event);
		}
	}
}
