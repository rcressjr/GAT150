#include "Engine.h"
#include "SDL_image.h"
#include <SDL.h>
#include <iostream>

int main(int, char**) {

	rj::Engine engine;
	engine.Startup();

	engine.Get<rj::Renderer>()->Create("GAT150", 800, 600);

	rj::Scene scene;
	scene.engine = &engine;

	rj::SetFilePath("../Resources");

	std::shared_ptr<rj::Texture> texture = engine.Get<rj::ResourceSystem>()->Get<rj::Texture>("sf2.png", engine.Get<rj::Renderer>());

	for (size_t i = 0; i < 50; i++) {
		rj::Transform transform{ rj::Vector2{ rj::RandomRangeInt(0, 800), rj::RandomRangeInt(0, 600) }, rj::RandomRange(0, 360), 1 };
		std::unique_ptr<rj::Actor> actor = std::make_unique<rj::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}

	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;


	while(!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			break;
		}

		engine.Update(0);
		scene.Update(engine.time.deltaTime);

		if (engine.time.time >= quitTime) quit = true;

		engine.time.timeScale = 2;

		engine.Get<rj::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<rj::Renderer>());
			
		engine.Get<rj::Renderer>()->EndFrame();
	}

	IMG_Quit();

	SDL_Quit();

	return 0;
}
