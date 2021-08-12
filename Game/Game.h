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
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const rj::Event& event);
	void OnPlayerDead(const rj::Event& event);
	void OnPlayerHurt(const rj::Event& event);

public:
	size_t lives = 0;
	std::unique_ptr<rj::Scene> scene;
	std::unique_ptr<rj::Engine> engine;

private:
	bool quit = false;
	float stateTimer = 0.0f;
	eState state = eState::Title;

	void (Game::*stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t level = 1;
	size_t creating = 1;
	std::string currentString;

	rj::AudioChannel musicChannel;
	std::shared_ptr<rj::Texture> texture;
	std::shared_ptr<rj::Texture> textTexture;
	std::shared_ptr<rj::Texture> particleTexture;
};