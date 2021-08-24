#pragma once

#define REGISTER_CLASS(class) ObjectFactory::Instance().Register<class>(#class);

// Audio
#include "Audio/AudioChannel.h"
#include "Audio/AudioSystem.h"

// Core
#include "Core/FileSystem.h"
#include "Core/Json.h"
#include "Core/Serializable.h"
#include "Core/Timer.h"
#include "Core/Utilities.h"

// Framework
#include "Framework/EventSystem.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"
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

// Components
#include "Math/Component/SpriteAnimationComponent.h"
#include "Math/Component/PhysicsComponent.h"

// Object
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Object/Scene.h"

// Resource
#include "Resource/Resource.h"
#include "Resource/ResourceSystem.h"

#define NOMINMAX
#include <vector>
#include <algorithm>
#include <memory>

namespace rj {
	
	using ObjectFactory = Singleton<Factory<std::string, Object>>;

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