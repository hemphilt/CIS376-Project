#include "player.h"
#include "projectile.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>




Player::Player(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
	: projectiles(),
	lastShotTime(0),
      	shotCooldown(1000){
	

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

std::vector<Projectile>& Player::getProjectiles() {
        return projectiles;
}

void Player::setProjectiles(const std::vector<Projectile>& newProjectiles) {
	projectiles = newProjectiles;
}

void Player::addProjectile( Projectile& projectile) {
        projectiles.push_back(projectile);
}

void Player::shootProjectile(SDL_Renderer* renderer) {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    // Check if right mouse button is pressed and if enough time has passed since the last shot
    if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT) && canShoot()) {
        Projectile newProjectile(renderer, "./assets/arrow.png", position.x, position.y, 20, 20);

        // Set the velocity of the projectile based on the mouse direction
        int deltaX = mouseX - position.x;
        int deltaY = mouseY - position.y;

        // Normalize the direction
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
        if (distance > 0) {
            newProjectile.setVelocityX(deltaX / distance * newProjectile.PROJECTILE_SPEED);
            newProjectile.setVelocityY(deltaY / distance * newProjectile.PROJECTILE_SPEED);
        }

        // Add the new projectile to the vector
        addProjectile(newProjectile);
        //printf("Creating a new projectile at (%d, %d)\n", position.x, position.y);  // Debug print

        // Update the last shot time
        lastShotTime = SDL_GetTicks();
    }
}

bool Player::canShoot() const {
    // Check if enough time has passed since the last shot
    return SDL_GetTicks() - lastShotTime >= shotCooldown;
}
