#include "Texture.h"
#include "Renderer.h"
#include <SDL_image.h>
#include <iostream>

namespace rj {
	bool Texture::Load(const std::string& name, void* data) {
		renderer = static_cast<Renderer*>(data)->renderer;
		//SDL_Surface* surface = SDL_LoadBMP("sf2.bmp");
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}
		
		return true;
	}

	Vector2 Texture::GetSize() const {
		SDL_Point point;
		SDL_QueryTexture(texture, nullptr, nullptr, &point.x, &point.y);

		return Vector2{ point.x, point.y };
	}
}