#pragma once
#include "Framework/System.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <vector>

namespace rj {

	class Texture;

	class ParticleSystem : public GraphicsSystem {
	public:
		struct Particle {
			Vector2 position;
			Vector2 prevPosition;
			Vector2 velocity;
			std::shared_ptr<Texture> texture;

			float lifetime;
			bool isActive{ false };
		
			static bool IsNotActive(Particle particle) { return particle.isActive == false; }
		};
	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(class Renderer* renderer) override;

		void Create(Vector2 position, size_t count, std::shared_ptr<Texture> texture, float lifetime, float speed);
		void Create(Vector2 position, size_t count, const std::vector<Color>& colors, float lifetime, float speed, float angle, float angleRange);

	private:
		std::vector<Particle> particles;
	};
}