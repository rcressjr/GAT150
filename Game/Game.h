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

public:
	std::unique_ptr<rj::Scene> scene;
	std::unique_ptr<rj::Engine> engine;

private:
	bool quit = false;
};