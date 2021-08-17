#include "Enemy.h"
#include "Math/MathUtils.h"
#include "Player.h"
#include "Projectile.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	if (scene->GetActor<Player>()) {
		rj::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		rj::Vector2 forward = rj::Vector2::Rotate(rj::Vector2::right, transform.rotation);

		float turnAngle = rj::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + (turnAngle * (3 * dt));

		transform.rotation = rj::Lerp(transform.rotation, transform.rotation + turnAngle, 2 * dt);

		float angle = rj::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= rj::QuarterPi) {
			fireTimer = fireRate;

			rj::Transform t = transform;
			t.scale = 0.5f;
			scene->AddActor(std::make_unique<Projectile>(t, scene->engine->Get<Game>()->enemyBulletTexture, 300.0f));
			scene->engine->Get<rj::AudioSystem>()->PlayAudio("EnemyFire");
		}
	}


	transform.position += rj::Vector2::Rotate(rj::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = rj::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = rj::Wrap(transform.position.y, 0.0f, 800.0f);
}

void Enemy::OnCollision(Actor* actor) {
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		destroy = true;
		scene->engine->Get<rj::ParticleSystem>()->Create(transform.position, 200, scene->engine->Get<Game>()->particleTextureTwo, 1, 50);
		scene->engine->Get<rj::AudioSystem>()->PlayAudio("EnemyDied");

		rj::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<rj::EventSystem>()->Notify(event);
	}
}
