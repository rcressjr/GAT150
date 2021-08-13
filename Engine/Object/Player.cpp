#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

Player::Player(const rj::Transform& transform, std::shared_ptr<rj::Texture> texture, float speed) : Actor{ transform, texture }  {
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ -8, 0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ 0, 5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = rj::Vector2{ 0, -5 };
	AddChild(std::move(locator));
}

void Player::Initialize() {
	
}

void Player::Update(float dt) {
	Actor::Update(dt);

	//movement
	float thrust = 0;
	if (scene->engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == rj::InputSystem::eKeyState::Held) transform.rotation += -5 * dt;
	if (scene->engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == rj::InputSystem::eKeyState::Held) transform.rotation += 5 * dt;
	if (scene->engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == rj::InputSystem::eKeyState::Held) thrust = speed;
	
	transform.position.x = rj::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = rj::Wrap(transform.position.y, 0.0f, 800.0f);

	rj::Vector2 acceleration;
	acceleration += rj::Vector2::Rotate(rj::Vector2::right, transform.rotation) * thrust;
	//rj::Vector2 gravity = (rj::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	//rj::Vector2 gravity = rj::Vector2::down * 50;
	//acceleration += gravity;

	velocity += acceleration * dt;
	transform.position += velocity * dt;

	velocity *= 0.99f;

	// fire
	fireTimer -= dt;
	if (fireTimer <= 0 && scene->engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == rj::InputSystem::eKeyState::Pressed) {
		fireTimer = fireRate;
		{
			rj::Transform t = children[1]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<Game>()->playerBulletTexture, 400.0f);
			projectile->transform.localPosition = rj::DegToRad(180);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}

		{
			rj::Transform t = children[2]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<Game>()->playerBulletTexture, 400.0f);
			projectile->transform.localPosition = rj::DegToRad(180);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}
		//scene->engine->Get<rj::AudioSystem>()->PlayAudio("PlayerShoot");
	}
	
	rocketTimer -= dt;
	if (rocketTimer <= 0 && scene->engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_LSHIFT || SDL_SCANCODE_RSHIFT) == rj::InputSystem::eKeyState::Pressed) {
		rocketTimer = rocketRate;
		rj::Transform t = children[0]->transform;
		std::unique_ptr<Projectile> rocket = std::make_unique<Projectile>(t, scene->engine->Get<Game>()->playerRocketTexture, 400.0f);
		rocket->transform.localPosition = rj::DegToRad(180);
		rocket->tag = "Player";
		scene->AddActor(std::move(rocket));
	}

	scene->engine->Get<rj::ParticleSystem>()->Create(children[0]->transform.position, 10, scene->engine->Get<Game>()->particleTexture, 3, 150, children[0]->transform.rotation, rj::DegToRad(30));
}

void Player::OnCollision(Actor* actor) {
	if (dynamic_cast<Enemy*>(actor)) {
		scene->engine->Get<rj::ParticleSystem>()->Create(transform.position, 200, scene->engine->Get<Game>()->particleTextureTwo, 1, 50);
		scene->engine->Get<rj::AudioSystem>()->PlayAudio("explosion");

		if (lives <= 0) {
			destroy = true;
			rj::Event event;
			event.name = "PlayerDead";
			event.data = "yes I'm dead!";
			scene->engine->Get<rj::EventSystem>()->Notify(event);
		}
		else {
			lives--;
			rj::Event event;
			event.name = "PlayerHurt";
			event.data = "yes, I took damage";
			scene->engine->Get<rj::EventSystem>()->Notify(event);
		}
	}
}
