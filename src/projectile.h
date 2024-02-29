#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//#include "/home/hemphito/CIS376/LEAGUE_Project/include/SDL2/SDL_image.h"

class Projectile {
public:
	Projectile(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
	~Projectile();

	void update();
	void render(SDL_Renderer* renderer, int offsetX, int offsetY);

	// Getters
	SDL_Rect getPosition() const;

private:
	SDL_Texture* texture;
	SDL_Rect position;
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
	const float PROJECTILE_SPEED = 5.0f;
};

#endif // PROJECTILE_H
