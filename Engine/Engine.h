#pragma once
// Audio
//#include "Audio/AudioSystem.h"

// Core
#include "Core/FileSystem.h"
#include "Core/Timer.h"

// Framework
#include "Framework/EventSystem.h"
#include "Framework/System.h"

// Input
#include "Input/InputSystem.h"

// Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

// Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/ParticleSystem.h"

// Resource
#include "Resource/ResourceSystem.h"

// Object
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Object/Scene.h"

#define NOMINMAX
#include <vector>
#include <algorithm>
#include <memory>

namespace rj {
	
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get() {
		for (auto& system : systems) {
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}

		return nullptr;
	}
}