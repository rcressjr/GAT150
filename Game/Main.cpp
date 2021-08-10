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

	engine.Get<rj::AudioSystem>()->AddAudio("explosion", "audio/PlayerShoot.wav");
	engine.Get<rj::AudioSystem>()->AddAudio("music", "audio/bensound-house.mp3");
	rj::AudioChannel channel = engine.Get<rj::AudioSystem>()->PlayAudio("music");

	std::shared_ptr<rj::Texture> texture = engine.Get<rj::ResourceSystem>()->Get<rj::Texture>("sf2.png", engine.Get<rj::Renderer>());
	std::shared_ptr<rj::Texture> particle = engine.Get<rj::ResourceSystem>()->Get<rj::Texture>("particle01.png", engine.Get<rj::Renderer>());

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

		if (engine.Get<rj::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == rj::InputSystem::eKeyState::Pressed) {
			quit = true;
		}

		if (engine.Get<rj::InputSystem>()->GetButtonState((int)rj::InputSystem::eMouseButton::Left) == rj::InputSystem::eKeyState::Pressed) {
			rj::Vector2 position = engine.Get<rj::InputSystem>()->GetMousePosition();
			engine.Get<rj::ParticleSystem>()->Create(position, 10, particle, 10, 50);
			engine.Get<rj::AudioSystem>()->PlayAudio("explosion", 1, rj::RandomRange(-20.0f, 2.0f));
			channel.SetPitch(rj::RandomRange(-2.0f, 2.0f));
		}

		engine.time.timeScale = 2;

		engine.Get<rj::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<rj::Renderer>());
		engine.Draw(engine.Get<rj::Renderer>());
			
		engine.Get<rj::Renderer>()->EndFrame();
	}

	IMG_Quit();

	SDL_Quit();

	return 0;
}
