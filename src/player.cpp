#include "player.h"
#include "projectile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



Player::Player(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
	: projectile(renderer, "/home/hemphito/CIS376/CIS376-Project/assets/arrow.png", x, y, 10, 10) {
	
	texture = loadTexture(renderer, imagePath);
	position.x = x;
	position.y = y;
	position.w = width;
	position.h = height;

	health = 100;
	mana = 50;
	playerClass = "Warrior";
}

Player::~Player() {
    	SDL_DestroyTexture(texture);
}

void Player::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
	SDL_Rect renderPosition = position;
	renderPosition.x += offsetX;
	renderPosition.y += offsetY;
	//printf("Rendering player at (%d, %d)\n", renderPosition.x, renderPosition.y);  // Debug print
	SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
}

SDL_Texture* Player::loadTexture(SDL_Renderer* renderer, const std::string& path) {
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

void Player::updatePosition(const Uint8* currentKeyStates) {
	// Update player position based on continuously pressed keys
	if (currentKeyStates[SDL_SCANCODE_W]) {
		position.y -= 2; // Move up
	}
	if (currentKeyStates[SDL_SCANCODE_S]) {
		position.y += 2; // Move down
	}
	if (currentKeyStates[SDL_SCANCODE_A]) {
		position.x -= 2; // Move left
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		position.x += 2; // Move right
	}
}

// Getters
int Player::getHealth() const {
	return health;
}

int Player::getMana() const {
	return mana;
}

std::string Player::getPlayerClass() const {
	return playerClass;
}

// Setters
void Player::setHealth(int newHealth) {
	health = newHealth;
}

void Player::setMana(int newMana) {
	mana = newMana;
}

void Player::setPlayerClass(const std::string& newPlayerClass) {
	playerClass = newPlayerClass;
}

const SDL_Rect Player::getPosition() const {
	return position;
}

Projectile& Player::getProjectile() {
    return projectile;
}

void Player::shootProjectile(SDL_Renderer* renderer) {
	// Set the velocity of the projectile based on the mouse direction
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int deltaX = mouseX - position.x;
	int deltaY = mouseY - position.y;

	// Normalize the direction
	float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance > 0) {
		projectile.setVelocityX(deltaX / distance * projectile.PROJECTILE_SPEED);
		projectile.setVelocityY(deltaY / distance * projectile.PROJECTILE_SPEED);
	}
}


