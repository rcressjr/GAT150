#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	engine->Get<rj::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent)
	REGISTER_CLASS(EnemyComponent)
	REGISTER_CLASS(PickupComponent)

	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	rj::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	rj::SetFilePath("../Resources");

	rapidjson::Document document;
	bool success = rj::json::Load("scene.txt", document);
	assert(success);

	scene->Read(document);

	auto actor = rj::ObjectFactory::Instance().Create<rj::Actor>("coin");
	actor->transform.position = rj::Vector2{ rj::RandomRange(0, 800), rj::RandomRange(100, 300) };
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