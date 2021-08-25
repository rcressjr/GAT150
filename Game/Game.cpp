#include "Game.h"
#include "Actors/Enemy.h"
#include "Actors/Player.h"
#include "Actors/Projectile.h"

void Game::Initialize() {
	engine = std::make_unique<rj::Engine>();
	engine->Startup();
	engine->Get<rj::Renderer>()->Create("GAT150", 800, 600);

	scene = std::make_unique<rj::Scene>();
	scene->engine = engine.get();

	rj::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	rj::SetFilePath("../Resources");

	engine->Get<rj::AudioSystem>()->AddAudio("explosion", "audio/PlayerShoot.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("music", "audio/bensound-house.mp3");
	musicChannel = engine->Get<rj::AudioSystem>()->PlayAudio("music", 1, 1, true);

	int size = 48;
	int titleSize = 64;
	font = engine->Get<rj::ResourceSystem>()->Get<rj::Font>("fonts/ace records.ttf", &size);
	titleFont = engine->Get<rj::ResourceSystem>()->Get<rj::Font>("fonts/endor.ttf", &titleSize);

	textTexture = std::make_shared<rj::Texture>(engine->Get<rj::Renderer>());
	titleTexture = std::make_shared<rj::Texture>(engine->Get<rj::Renderer>());
	playerTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("player.png", engine->Get<rj::Renderer>());
	playerBulletTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("bullet.png", engine->Get<rj::Renderer>());
	playerRocketTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("missile.png", engine->Get<rj::Renderer>());
	enemyTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("enemy.png", engine->Get<rj::Renderer>());
	enemyBulletTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("eboylet.png", engine->Get<rj::Renderer>());
	particleTexture = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("particle01.png", engine->Get<rj::Renderer>());
	particleTextureTwo = engine->Get<rj::ResourceSystem>()->Get<rj::Texture>("particle02.png", engine->Get<rj::Renderer>());

	engine->Get<rj::ResourceSystem>()->Add("textTexture", textTexture);

	engine->Get<rj::AudioSystem>()->AddAudio("EnemyDied", "audio/EnemyKilled.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("EnemyFire", "audio/EnemyShoot.wav");
	engine->Get<rj::AudioSystem>()->AddAudio("PlayerShoot", "audio/PlayerShoot.wav");

	engine->Get<rj::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
	engine->Get<rj::EventSystem>()->Subscribe("PlayerHurt", std::bind(&Game::OnPlayerHurt, this, std::placeholders::_1));
}

void Game::Shutdown() {
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {
	engine->Update();
	engine->time.timeScale = 2;
	scene->Update(engine->time.deltaTime);

	switch (state) {
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
		UpdateLevelStart(engine->time.deltaTime);

		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0) {
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
		}
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	if (engine->Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == rj::InputSystem::eKeyState::Pressed) {
		quit = true;
	}

	if (engine->Get<rj::InputSystem>()->GetButtonState((int)rj::InputSystem::eMouseButton::Left) == rj::InputSystem::eKeyState::Pressed) {
		rj::Vector2 position = engine->Get<rj::InputSystem>()->GetMousePosition();
		engine->Get<rj::ParticleSystem>()->Create(position, 10, particleTexture, 10, 50);
		engine->Get<rj::AudioSystem>()->PlayAudio("explosion", 1, rj::RandomRange(-20.0f, 2.0f));
	}
}

void Game::Draw() {
	engine->Get<rj::Renderer>()->BeginFrame();

	switch (state) {
	case Game::eState::Title:
		titlepos.position = { 375, 300 };
		titleTexture->Create(titleFont->CreateSurface("VECTORY WARS", rj::Color::purple));
		engine->Get<rj::Renderer>()->Draw(titleTexture, titlepos);

		t.position = { 400, 400 };
		textTexture->Create(font->CreateSurface("Press Space to Start", rj::Color::purple));
		engine->Get<rj::Renderer>()->Draw(textTexture, t);

		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		currentString = "level  " + std::to_string(level);
		textTexture->Create(font->CreateSurface(currentString, rj::Color::white));

		levelpos.position = { 400, 20 };
		engine->Get<rj::Renderer>()->Draw(textTexture, levelpos);

		break;
	case Game::eState::GameOver:
		textTexture->Create(font->CreateSurface("Game Over", rj::Color::red));

		t.position = { 350, 300 };
		engine->Get<rj::Renderer>()->Draw(textTexture, t);

		break;
	default:
		break;
	}

	textTexture->Create(font->CreateSurface(std::to_string(score), rj::Color::white));
	t.position = { 30, 20 };
	engine->Get<rj::Renderer>()->Draw(textTexture, t);
	
	textTexture->Create(font->CreateSurface(std::to_string(lives), rj::Color::white));
	t.position = { 750, 20 };
	engine->Get<rj::Renderer>()->Draw(textTexture, t);

	engine->Draw(engine->Get<rj::Renderer>());
	scene->Draw(engine->Get<rj::Renderer>());

	engine->Get<rj::Renderer>()->EndFrame();
}

void Game::UpdateLevelStart(float dt) {
	engine->Get<rj::Renderer>()->BeginFrame();
	if (scene->GetActors<Player>().size() == 0) {
		scene->AddActor(std::make_unique<Player>(rj::Transform{ rj::Vector2{ 400, 300 }, 0, 3 }, playerTexture, 300.0f));

	}

	for (size_t i = 0; i < creating; i++) {
		scene->AddActor(std::make_unique<Enemy>(rj::Transform{ rj::Vector2{ rj::RandomRangeInt(0, 800), rj::RandomRangeInt(0, 600) }, rj::RandomRange(0.0f, rj::TwoPi), 2 }, enemyTexture, 150.0f));
		
	}

	engine->Get<rj::Renderer>()->EndFrame();
	state = eState::Game;
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
