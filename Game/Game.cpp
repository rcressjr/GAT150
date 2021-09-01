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

	engine->Get<rj::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {
	engine->Update();
	
	if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == rj::InputSystem::eKeyState::Pressed) quit = true;

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	auto scoreActor = scene->FindActor("score");
	if (scoreActor) {
		scoreActor->GetComponent<rj::TextComponent>()->SetText(std::to_string(score));
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw() {
	engine->Get<rj::Renderer>()->BeginFrame();


	engine->Draw(engine->Get<rj::Renderer>());
	scene->Draw(engine->Get<rj::Renderer>());

	engine->Get<rj::Renderer>()->EndFrame();
}

void Game::Reset() {
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = rj::json::Load("title.txt", document);
	assert(success);

	scene->Read(document);

	state = eState::Title;
}

void Game::Title() {
	if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == rj::InputSystem::eKeyState::Pressed) {
		auto title = scene->FindActor("title");
		title->active = false;

		state = eState::StartGame;
	}
}

void Game::StartGame() {
	rapidjson::Document document;
	bool success = rj::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	rj::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = rj::json::Load("map.txt", document);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel() {
	stateTimer += engine->time.deltaTime;

	if (stateTimer >= 1) {
		auto player = rj::ObjectFactory::Instance().Create<rj::Actor>("Player");
		player->transform.position = rj::Vector2{ 400, 350 };

		scene->AddActor(std::move(player));

		spawnTimer = 2;

		state = eState::Level;
	}
}

void Game::Level() {
	spawnTimer -= engine->time.deltaTime;

	if (spawnTimer <= 0) {
		auto coin = rj::ObjectFactory::Instance().Create<rj::Actor>("coin");
		coin->transform.position = rj::Vector2{ rj::RandomRange(100, 700), 150.0f };

		scene->AddActor(std::move(coin));
	}
}

void Game::PlayerDead() {

}

void Game::GameOver() {

}

void Game::OnAddScore(const rj::Event& event) {
	score += std::get<int>(event.data);
}
