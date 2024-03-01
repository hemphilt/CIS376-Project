#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <SDL2/SDL.h>
#include <box2d/box2d.h>

#include "projectile.h"

class Enemy {
public:
    Enemy(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, float x, float y, float width, float height);
    ~Enemy();

    void render(SDL_Renderer* renderer, int offsetX, int offsetY);
    int getHealth() const;
    std::string getEnemyClass() const;
    void setHealth(int newHealth);
    void setEnemyClass(const std::string& newEnemyClass);
    void updatePosition(float playerX, float playerY);
    const SDL_Rect getPosition() const;

private:
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    void createBody(b2World* world, float x, float y);

    b2World* world;
    b2Body* body;
    SDL_Rect position;
    SDL_Texture* texture;
    int health;
    std::string enemyClass;
};

#endif // ENEMY_H
















/*
#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

const float ENEMY_SPEED = 2.0f;

class Enemy {

public:
	Enemy(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
    	~Enemy();
    	void render(SDL_Renderer* renderer, int offsetX, int offsetY);
    	const SDL_Rect getPosition() const; 
    	void updatePosition(const SDL_Rect& playerPosition);

    	// Getters
    	int getHealth() const;
    	std::string getEnemyClass() const;

    	// Setters
    	void setHealth(int health);
    	void setEnemyClass(const std::string& enemyClass);

private:
	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    	
	int health;
	std::string enemyClass;
};

#endif // ENEMY_H
*/
