#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;


class Projectile {
public:
	Projectile(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
	~Projectile();

	void update();
	void render(SDL_Renderer* renderer, int offsetX, int offsetY);

	// Getters
	SDL_Rect getPosition() const;
	
	float PROJECTILE_SPEED = 5.0f;
	
	void setVelocityX(float vx);
	void setVelocityY(float vy);
	
	bool isAlive() const;

private:
	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
	
	float velocityX;
	float velocityY;
};

#endif // PROJECTILE_H
