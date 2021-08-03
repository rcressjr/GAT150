#include "Engine.h"

namespace rj {
	void Engine::Startup() {
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });

		for (auto& system : systems) {
			std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });
		}
	}

	void Engine::Shutdown() {
		for (auto& system : systems) {
			std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Shutdown(); });
		}
	}

	void Engine::Update(float dt) {
		for (auto& system : systems) {
			std::for_each(systems.begin(), systems.end(), [dt](auto& system) {system->Update(dt); });
		}
	}

	void Engine::Draw() {
		//
	}
}