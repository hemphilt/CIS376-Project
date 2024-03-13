#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <string>
#include <map> 
#include <box2d/box2d.h>
#include "entityuserdata.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define ENEMY_SPEED 90.0f
#define PPM 100.0f


class Enemy {
public:
    Enemy(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, float x, float y, float width, float height);
    ~Enemy();

    void update(float playerX, float playerY, float deltaTime);
    void render(SDL_Renderer* renderer, int offsetX, int offsetY);
    const SDL_Rect getPosition() const;
    void setPosition(float x, float y);

    int getHealth() const;
    std::string getEnemyClass() const;
    void setHealth(int newHealth);
    void setEnemyClass(const std::string& newEnemyClass);
    
    void handleBeginContact(EntityUserData* otherUserData);

private:
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    void createBody(b2World* world, float x, float y);

    SDL_Rect position;
    SDL_Texture* texture;
    b2World* world;
    b2Body* body;
    int health;
    std::string enemyClass;
};

#endif // ENEMY_H
