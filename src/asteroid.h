#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//#include "/home/hemphito/CIS376/LEAGUE_Project/include/SDL2/SDL_image.h"

class Asteroid {

	public:
	    	Asteroid(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
	    	~Asteroid();
	    	void render(SDL_Renderer* renderer);

	private:
		SDL_Texture* texture;
		SDL_Rect position;
	    	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
};

#endif // ASTEROID_H
