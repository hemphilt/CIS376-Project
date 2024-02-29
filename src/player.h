#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "projectile.h"

class Player {

public:
	Player(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
    	~Player();
    	void render(SDL_Renderer* renderer, int offsetX, int offsetY);
    	void handleInput(SDL_Event& event);
    	const SDL_Rect getPosition() const; 
    	void updatePosition(const Uint8* currentKeyStates);
    	
    	void shootProjectile(SDL_Renderer* renderer);
    	const Projectile& getProjectile();

    	// Getters
    	int getHealth() const;
    	int getMana() const;
    	std::string getPlayerClass() const;

    	// Setters
    	void setHealth(int health);
    	void setMana(int mana);
    	void setPlayerClass(const std::string& playerClass);

private:
	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
    	
	int health;
	int mana;
	std::string playerClass;
	
	Projectile projectile;
};

#endif // PLAYER_H

