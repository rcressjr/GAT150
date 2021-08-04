#include "Engine.h"
#include "SDL_image.h"
#include <SDL.h>
#include <iostream>

int main(int, char**){
	rj::Engine engine;
	engine.Startup();

	engine.Get<rj::Renderer>()->Create("GAT150", 800, 600);

	std::cout << rj::GetFilePath() << std::endl;
	rj::SetFilePath("../Resources");
	std::cout << rj::GetFilePath() << std::endl;

	std::shared_ptr<rj::Texture> texture = engine.Get<rj::ResourceSystem>()->Get<rj::Texture>("sf2.png", engine.Get<rj::Renderer>());

	bool quit = false;
	SDL_Event event;
	while(!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			break;
		}

		engine.Get<rj::Renderer>()->BeginFrame();

		rj::Vector2 position{ 300, 400 };

		engine.Get<rj::Renderer>()->Draw(texture, position);

		engine.Get<rj::Renderer>()->EndFrame();

		//for (size_t i = 0; i < 250; i++) {
		//	SDL_Rect src{ 32, 64, 32, 64 };
		// 
		//	SDL_Rect dest{ rj::RandomRangeInt(0, screen.x), rj::RandomRangeInt(0, screen.y), 16, 24 };
		//	SDL_RenderCopy(renderer, texture, &src, &dest);
		//}
	}

	IMG_Quit();

	SDL_Quit();

	return 0;
}
