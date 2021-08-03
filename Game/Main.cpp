#include "Engine.h"
#include "SDL_image.h"
#include <SDL.h>
#include <iostream>

int main(int, char**)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::cout << rj::GetFilePath() << std::endl;
	rj::SetFilePath("../Resources");
	std::cout << rj::GetFilePath() << std::endl;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Surface* surface = SDL_LoadBMP("sf2.bmp");
	SDL_Surface* surface = IMG_Load("sf2.png");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);



	// load surface
	// create texture

	bool quit = false;
	SDL_Event event;
	while(!quit) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			break;
		}
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	IMG_Quit();

	SDL_Quit();

	return 0;
}
