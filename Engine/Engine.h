#pragma once
// Audio
#include "Audio/AudioChannel.h"
#include "Audio/AudioSystem.h"

// Core
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Utilities.h"

// Framework
#include "Framework/EventSystem.h"
#include "Framework/System.h"

// Graphics
#include "Graphics/Font.h"
#include "Graphics/ParticleSystem.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"

// Input
#include "Input/InputSystem.h"

// Math
#include "Math/Color.h"
#include "Math/MathUtils.h"
#include "Math/Matrix22.h"
#include "Math/Matrix33.h"
#include "Math/random.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"

// Object
#include "Object/Actor.h"
//#include "Object/Enemy.h"
#include "Object/Object.h"
//#include "Object/Player.h"
//#include "Object/Projectile.h"
#include "Object/Scene.h"

// Resource
#include "Resource/Resource.h"
#include "Resource/ResourceSystem.h"

#define NOMINMAX
#include <vector>
#include <algorithm>
#include <memory>

namespace rj {
	
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update();
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