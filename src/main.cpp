// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: g++ main.cpp -o main -lSDL2
// run with: ./main
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//#include </home/hemphito/CIS376/LEAGUE_Project/include/SDL2/SDL_image.h>

#include "spaceship.h"
#include "enemy.h"
#include "asteroid.h"
#include "planet.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
  	SDL_Window* window = NULL;
  	SDL_Renderer* renderer = NULL;
  	SDL_Surface* screenSurface = NULL;
  	SDL_Surface* backgroundImage = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
   		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    		return 1;
  	}
  
  	window = SDL_CreateWindow(
    		"main",
	    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	   	SCREEN_WIDTH, SCREEN_HEIGHT,
	    	SDL_WINDOW_SHOWN
	);
			    
  	if (window == NULL) {
    		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    		return 1;
  	}
 
 	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    	if (renderer == NULL) {
        	fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
        	return 1;
    	}
 
 
  	screenSurface = SDL_GetWindowSurface(window);
 	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
 
  	// Load background image
  	backgroundImage = IMG_Load("/home/hemphito/CIS376/LEAGUE_Project/Assets/Backgrounds/Starfields/Starfield6.png");
  	if (backgroundImage == NULL) {
	  	fprintf(stderr, "could not load image: %s\n", SDL_GetError());
	  	return 1;
  	}

  	// Blit the image onto the window surface
  	SDL_BlitSurface(backgroundImage, NULL, screenSurface, NULL);
  	
  	
  	// Create a Spaceship
  	Spaceship spaceship(renderer, "/home/hemphito/CIS376/LEAGUE_Project/assets/Player/Design/Ship.png", 100, 100, 50, 50);
  	spaceship.render(renderer);


	// Create an Enemy on the other side of the screen
 	Enemy enemy(renderer, "/home/hemphito/CIS376/LEAGUE_Project/assets/Enemies/Designs/Fighter.png", SCREEN_WIDTH - 100, 100, 50, 50);
  	enemy.render(renderer);
    

	// Create a Projectile coming from enemy
	Projectile projectile(renderer, "/path/to/projectile.png", enemy.getPosition().x - 75, enemy.getPosition().y, 20, 20);
	projectile.render(renderer);
	
	
	// Create two Asteroids
	Asteroid asteroid1(renderer, "/home/hemphito/CIS376/LEAGUE_Project/assets/Asteroids/Asteroid.png", 200, 200, 25, 30);
	asteroid1.render(renderer);
	
	Asteroid asteroid2(renderer, "/home/hemphito/CIS376/LEAGUE_Project/assets/Asteroids/Asteroid.png", 400, 300, 42, 42);
	asteroid2.render(renderer);


	// Create a Planet in the background
	Planet planet(renderer, "/home/hemphito/CIS376/LEAGUE_Project/assets/Planets/Gas - Giant/Giant1.png", 220, 50, 100, 100);
	planet.render(renderer);


 
	SDL_UpdateWindowSurface(window);
	SDL_Delay(10000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
