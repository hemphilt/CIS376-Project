#include "projectile.h"

Projectile::Projectile(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height) {
	texture = loadTexture(renderer, imagePath);
	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;
}

Projectile::~Projectile() {
	SDL_DestroyTexture(texture);
}

void Projectile::update() {
	// Move the projectile in its current direction
	position.x += static_cast<int>(PROJECTILE_SPEED);
}

void Projectile::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
	SDL_Rect renderPosition = position;
	renderPosition.x += offsetX;
	renderPosition.y += offsetY;
	SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
}

SDL_Rect Projectile::getPosition() const {
	return position;
}

SDL_Texture* Projectile::loadTexture(SDL_Renderer* renderer, const std::string& path) {
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


void Projectile::setVelocityX(float vx) {
    velocityX = vx;
}

void Projectile::setVelocityY(float vy) {
    velocityY = vy;
}

