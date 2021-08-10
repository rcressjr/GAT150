#include "Engine.h"

namespace rj {
	void Engine::Startup() {
		systems.push_back(std::make_unique<Renderer>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());
		systems.push_back(std::make_unique<InputSystem>());
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });
	}

	void Engine::Shutdown() {
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Shutdown(); });
	
	}

	void Engine::Update(float dt) {
		time.Tick();

		std::for_each(systems.begin(), systems.end(), [this](auto& system) {system->Update(this->time.deltaTime); });
		
	}

	void Engine::Draw(Renderer* renderer) {
		std::for_each(systems.begin(), systems.end(), [renderer](auto& system) { if (dynamic_cast<GraphicsSystem*>(system.get())) dynamic_cast<GraphicsSystem*>(system.get())->Draw(renderer); });
	}
}