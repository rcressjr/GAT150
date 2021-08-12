#include "Game.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	engine->Get<rj::Renderer>()->Create("GAT150", 800, 600);

	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	rj::SetFilePath("../Resources");

	engine->Get<rj::AudioSystem>()->AddAudio("explosion", "audio/PlayerShoot.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("music", "audio/bensound-house.mp3");
	musicChannel = engine->Get<rj::AudioSystem>()->PlayAudio("music", 1, 1, true);

	int size = 64;
	std::shared_ptr<rj::Font> font = engine->Get<rj::ResourceSystem>()->Get<rj::Font>("fonts/ace records.ttf", &size);

	textTexture = std::make_shared<rj::Texture>(engine->Get<rj::Renderer>());
	texture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("sf2.png", engine->Get<rj::Renderer>());
	particleTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("particle01.png", engine->Get<rj::Renderer>());

	textTexture->Create(font->CreateSurface("hello world", rj::Color::purple));

	engine->Get<rj::ResourceSystem>()->Add("textTexture", textTexture);

	for (size_t i = 0; i < 50; i++) {
		rj::Transform transform{ rj::Vector2{ rj::RandomRangeInt(0, 800), rj::RandomRangeInt(0, 600) }, rj::RandomRange(0, 360), 1 };
		std::unique_ptr<rj::Actor> actor = std::make_unique<rj::Actor>(transform, texture);
		scene->AddActor(std::move(actor));
	}

	// game
	engine->Get<rj::AudioSystem>()->AddAudio("EnemyDied", "EnemyKilled.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("EnemyFire", "EnemyShoot.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("PlayerShoot", "PlayerShoot.wav");

	engine->Get<rj::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerHurt", std::bind(&Game::OnPlayerHurt, this, std::placeholders::_1));

	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {
	float dt = engine->time.deltaTime;

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == rj::InputSystem::eKeyState::Pressed) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 18;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	case Game::eState::Game:
		/*if (scene->GetActors<Enemy>().size() == 0) {
			level++;
			if (level >= 10 && level < 20) {
				creating = 10;
			}
			else if (level >= 20 && level < 30) {
				creating = 15;
			}
			else if (level >= 30 && level < 40) {
				creating = 20;
			}
			else if (level >= 40 && level < 50) {
				creating = 25;
			}
			else if (level >= 50) {
				creating += 5;
			}

			state = eState::StartLevel;
		}*/
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);;

	if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == rj::InputSystem::eKeyState::Pressed) {
		quit = true;
	}

	if (engine->Get<rj::InputSystem>()->GetButtonState((int)rj::InputSystem::eMouseButton::Left) == rj::InputSystem::eKeyState::Pressed) {
		rj::Vector2 position = engine->Get<rj::InputSystem>()->GetMousePosition();
		engine->Get<rj::ParticleSystem>()->Create(position, 10, particleTexture, 10, 50);
		engine->Get<rj::AudioSystem>()->PlayAudio("explosion", 1, rj::RandomRange(-20.0f, 2.0f));
		musicChannel.SetPitch(rj::RandomRange(-2.0f, 2.0f));
	}
}

void Game::Draw() {
	switch (state)
	{
	case Game::eState::Title:
		/*graphics.SetColor(rj::Color::purple);
		graphics.DrawString(300, 300 + std::sin(stateTimer * 3) * 250, "VECTORY WARS");
		graphics.SetColor(rj::Color::blue);
		graphics.DrawString(320, 350, "Press Space to Start");*/

		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel: {
		break;
	}
	case Game::eState::Game:
		/*currentString = "level  " + std::to_string(level);
		graphics.SetColor(rj::Color::white);
		graphics.DrawString(400, 20, currentString.c_str());*/
		break;
	case Game::eState::GameOver:
		/*graphics.SetColor(rj::Color::red);
		graphics.DrawString(350, 300, "Game Over");*/
		break;
	default:
		break;
	}

	/*graphics.SetColor(rj::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());*/

	engine->Get<rj::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<rj::Renderer>());
	engine->Draw(engine->Get<rj::Renderer>());

	rj::Transform t;
	t.position = { 30, 30 };
	engine->Get<rj::Renderer>()->Draw(textTexture, t);

	engine->Get<rj::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt) {
	/*if (Core::Input::IsPressed(VK_SPACE)) {
		stateFunction = &Game::UpdateLevelStart;
		state = eState::StartGame;
	}*/
}

void Game::UpdateLevelStart(float dt) {
	/*if (scene->GetActors<Player>().size() == 0) {
		scene->AddActor(std::make_unique<Player>(rj::Transform{ rj::Vector2(400, 300), 0, 3 }, engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("shape.txt"), 300.0f));
	}
	for (size_t i = 0; i < creating; i++) {
		scene->AddActor(std::make_unique<Enemy>(rj::Transform{ rj::Vector2(rj::RandomEnemy(0.0f, 800.0f), rj::RandomEnemy(0.0f, 600.0f)), rj::RandomEnemy(0.0f, rj::TwoPi), 2 }, engine->Get<rj::ResourceSystem>()->Get<rj::Shape>("enemy.txt"), 150.0f));
	}

	state = eState::Game;*/
}

void Game::OnAddPoints(const rj::Event& event) {
	score += std::get<int>(event.data);
}

void Game::OnPlayerHurt(const rj::Event& event) {
	lives--;
}

void Game::OnPlayerDead(const rj::Event& event) {
	state = eState::GameOver;
}
