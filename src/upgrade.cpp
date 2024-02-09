#include "upgrade.h"

Upgrade::Upgrade(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height) {
	texture = loadTexture(renderer, imagePath);
	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;
}

Upgrade::~Upgrade() {
	SDL_DestroyTexture(texture);
}

void Upgrade::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, nullptr, &position);
}

SDL_Texture* Upgrade::loadTexture(SDL_Renderer* renderer, const std::string& path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
    		return nullptr;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	if (texture == nullptr) {
    		return nullptr;
	}
	
	return texture;
}

