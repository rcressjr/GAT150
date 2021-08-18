#include "Game.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	engine->Get<rj::Renderer>()->Create("GAT150", 800, 600);

	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	rj::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	rj::SetFilePath("../Resources");

	//std::unique_ptr<rj::Actor> actor = std::make_unique<rj::Actor>(rj::Transform( rj::Vector2{ 400, 300 }, 0, 1 ));
	/*{
		rj::SpriteComponent* component = actor->AddComponent<rj::SpriteComponent>();
		component->texture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("luma.png", engine->Get<rj::Renderer>());
	}*/
	std::unique_ptr<rj::Actor> actor = std::make_unique <rj::Actor>(rj::Transform{ rj::Vector2{400, 300}, 0, 7 });
	{
		rj::SpriteAnimationComponent* component = actor->AddComponent<rj::SpriteAnimationComponent>();
		component->texture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("rosalina.png", engine->Get<rj::Renderer>());
		component->fps = 24;
		component->numFramesX = 12;
		component->numFramesY = 8;
	}
	/*{
		rj::PhysicsComponent* component = actor->AddComponent<rj::PhysicsComponent>();
		component->ApplyForce(rj::Vector2::right * 200);
	}*/
	scene->AddActor(std::move(actor));
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {
	engine->Update();
	
	if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == rj::InputSystem::eKeyState::Pressed) quit = true;

	scene->Update(engine->time.deltaTime);
}

void Game::Draw() {
	engine->Get<rj::Renderer>()->BeginFrame();


	engine->Draw(engine->Get<rj::Renderer>());
	scene->Draw(engine->Get<rj::Renderer>());

	engine->Get<rj::Renderer>()->EndFrame();
}