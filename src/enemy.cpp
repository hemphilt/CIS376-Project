#include "enemy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Enemy::Enemy(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height) {
	texture = loadTexture(renderer, imagePath);
	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;


	health = 100;
	enemyClass = "Warrior";
}

Enemy::~Enemy() {
    	SDL_DestroyTexture(texture);
}

void Enemy::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
	SDL_Rect renderPosition = position;
	renderPosition.x += offsetX;
	renderPosition.y += offsetY;
	SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
}

SDL_Texture* Enemy::loadTexture(SDL_Renderer* renderer, const std::string& path) {
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


// Getters
int Enemy::getHealth() const {
	return health;
}

std::string Enemy::getEnemyClass() const {
	return enemyClass;
}

// Setters
void Enemy::setHealth(int newHealth) {
	health = newHealth;
}

void Enemy::setEnemyClass(const std::string& newEnemyClass) {
	enemyClass = newEnemyClass;
}

void Enemy::updatePosition(const SDL_Rect& playerPosition) {
	// Calculate the direction towards the player
	int deltaX = playerPosition.x - position.x;
	int deltaY = playerPosition.y - position.y;

	// Calculate the distance to the player
	float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

	// Check if the player is within 100 pixels
	if (distance <= 300) {
		// Normalize the direction
		if (distance > 0) {
			deltaX = static_cast<int>(deltaX / distance * ENEMY_SPEED);
			deltaY = static_cast<int>(deltaY / distance * ENEMY_SPEED);
		}

		// Update the enemy position based on the calculated direction
		position.x += deltaX;
		position.y += deltaY;
	}
}

const SDL_Rect Enemy::getPosition() const {
	return position;
}

