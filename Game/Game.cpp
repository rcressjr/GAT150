#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	engine->Get<rj::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent)
	REGISTER_CLASS(EnemyComponent)

	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	rj::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	rj::SetFilePath("../Resources");

	rapidjson::Document document;
	bool success = rj::json::Load("scene.txt", document);
	assert(success);

	scene->Read(document);

	//std::unique_ptr<rj::Actor> actor = std::make_unique<rj::Actor>(rj::Transform( rj::Vector2{ 400, 300 }, 0, 1 ));
	/*{
		rj::SpriteComponent* component = actor->AddComponent<rj::SpriteComponent>();
		component->texture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("luma.png", engine->Get<rj::Renderer>());
	}*/

	/*std::unique_ptr<rj::Actor> actor = std::make_unique <rj::Actor>(rj::Transform{ rj::Vector2{400, 300}, 0, 7 });
	{
		auto component = rj::ObjectFactory::Instance().Create<rj::SpriteAnimationComponent>("SpriteAnimationComponent");
		component->texture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("rosalinawalkright.png", engine->Get<rj::Renderer>());
		component->fps = 24;
		component->numFramesX = 12;
		component->numFramesY = 2;
		actor->AddComponent(std::move(component));
	}
	{
		auto component = rj::ObjectFactory::Instance().Create<rj::PhysicsComponent>("PhysicsComponent");
		component->ApplyForce(rj::Vector2::right * 10);
		actor->AddComponent(std::move(component));
	}
	scene->AddActor(std::move(actor));*/
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