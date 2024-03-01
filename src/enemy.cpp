#include "enemy.h"
#include <SDL2/SDL_image.h>
#include <cmath>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define ENEMY_SPEED 1.75f
#define PPM 32.0f

Enemy::Enemy(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, float x, float y, float width, float height)
    : world(world),
      body(nullptr),
      texture(nullptr) {
    texture = loadTexture(renderer, imagePath);
    position.x = static_cast<int>(x);
    position.y = static_cast<int>(y);
    position.w = static_cast<int>(width);
    position.h = static_cast<int>(height);
    health = 100;
    enemyClass = "Warrior";

    createBody(world, x, y);
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
    world->DestroyBody(body);
}

SDL_Texture* Enemy::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void Enemy::createBody(b2World* world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PPM, y / PPM);
    bodyDef.fixedRotation = true;  // Prevent player from rotating

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(position.w / 2 / PPM, position.h / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void Enemy::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect renderPosition = position;
    renderPosition.x += offsetX;
    renderPosition.y += offsetY;
    SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
}

int Enemy::getHealth() const {
    return health;
}

std::string Enemy::getEnemyClass() const {
    return enemyClass;
}

void Enemy::setHealth(int newHealth) {
    health = newHealth;
}

void Enemy::setEnemyClass(const std::string& newEnemyClass) {
    enemyClass = newEnemyClass;
}

void Enemy::updatePosition(float playerX, float playerY) {
    // Calculate the direction towards the player
    float deltaX = playerX - position.x;
    float deltaY = playerY - position.y;

    // Calculate the distance to the player
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    // Check if the player is within 300 pixels
    if (distance <= 300) {
        // Normalize the direction
        if (distance > 0) {
            deltaX = deltaX / distance * ENEMY_SPEED;
            deltaY = deltaY / distance * ENEMY_SPEED;
        }

        // Update the enemy position based on the calculated direction
        position.x += static_cast<int>(deltaX);
        position.y += static_cast<int>(deltaY);
    }
}

const SDL_Rect Enemy::getPosition() const {
    return position;
}















/*
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
*/
