#pragma once
#include "Engine.h"



class Game {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }

private:
	void UpdateLevelStart(float dt);
	void OnAddPoints(const rj::Event& event);
	void OnPlayerDead(const rj::Event& event);
	void OnPlayerHurt(const rj::Event& event);

public:
	size_t lives = 0;
	std::unique_ptr<rj::Scene> scene;
	std::unique_ptr<rj::Engine> engine;

	rj::AudioChannel musicChannel;
	std::shared_ptr<rj::Font> font;
	std::shared_ptr<rj::Font> titleFont;
	std::shared_ptr<rj::Texture> playerTexture;
	std::shared_ptr<rj::Texture> playerBulletTexture;
	std::shared_ptr<rj::Texture> playerRocketTexture;
	std::shared_ptr<rj::Texture> enemyTexture;
	std::shared_ptr<rj::Texture> enemyBulletTexture;
	std::shared_ptr<rj::Texture> textTexture;
	std::shared_ptr<rj::Texture> titleTexture;
	std::shared_ptr<rj::Texture> particleTexture;
	std::shared_ptr<rj::Texture> particleTextureTwo;
private:
	bool quit = false;
	float stateTimer = 0.0f;
	eState state = eState::Title;

	void (Game::*stateFunction)(float) = nullptr;
	rj::Transform t;
	rj::Transform titlepos;
	rj::Transform levelpos;

	size_t score = 0;
	size_t level = 1;
	size_t creating = 1;
	std::string currentString;
};