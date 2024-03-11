#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include "projectile.h"
#include "entityuserdata.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define PLAYER_SPEED 5.0f
#define PPM 32.0f

class Player {
public:
    Player(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
    ~Player();

    void setPosition(float x, float y);
    b2Body* getBody() const;
    void handleInput(SDL_Renderer* renderer, const Uint8* currentKeyStates);
    void render(SDL_Renderer* renderer, int offsetX, int offsetY);
    std::vector<Projectile>& getProjectiles();
    void setProjectiles(const std::vector<Projectile>& newProjectiles);
    int getHealth() const;
    
    void handleBeginContact(EntityUserData* otherUserData);

private:
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    void shootProjectile(SDL_Renderer* renderer);

    b2World* world;
    b2Body* body;
    SDL_Texture* texture;
    std::vector<Projectile> projectiles;
    int lastShotTime;
    int shotCooldown;
    int health;
    int mana;
    std::string playerClass;
    SDL_Rect position;
};

#endif // PLAYER_H
