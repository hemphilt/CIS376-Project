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

