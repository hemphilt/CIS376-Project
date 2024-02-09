#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//#include "/home/hemphito/CIS376/LEAGUE_Project/include/SDL2/SDL_image.h"

class Spaceship {

	public:
	    	Spaceship(SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height);
	    	~Spaceship();
	    	void render(SDL_Renderer* renderer);

	private:
		SDL_Texture* texture;
		SDL_Rect position;
	    	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path);
};

#endif // SPACESHIP_H
