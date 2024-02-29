#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "player.h"
#include "enemy.h"
#include "projectile.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800



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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);

    // Load background image
    backgroundImage = IMG_Load("/home/hemphito/CIS376/CIS376-Project/assets/dungeon.png");
    if (backgroundImage == NULL) {
        fprintf(stderr, "could not load image: %s\n", SDL_GetError());
        return 1;
    }

    // Create texture from the surface
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
    if (backgroundTexture == NULL) {
        fprintf(stderr, "could not create background texture: %s\n", SDL_GetError());
        SDL_FreeSurface(backgroundImage);
        return 1;
    }

    // Free the surface as it is no longer needed
    SDL_FreeSurface(backgroundImage);
    backgroundImage = NULL;

    // Create a Player
    Player player(renderer, "/home/hemphito/CIS376/CIS376-Project/assets/warrior.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 25, 50);

    // Create an Enemy on the other side of the screen
    Enemy enemy(renderer, "/home/hemphito/CIS376/CIS376-Project/assets/skeleton.png", SCREEN_WIDTH - 100, 100, 25, 50);

    SDL_UpdateWindowSurface(window);

    // Main game loop
bool quit = false;
Uint32 lastFrameTime = SDL_GetTicks();

while (!quit) {
   SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
            // Right-click to shoot
            player.shootProjectile(renderer);
        }
    }

    // Get the state of all keys
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    // Update player position based on continuously pressed keys
    player.updatePosition(currentKeyStates);

    // Update enemy position based on player's position
    enemy.updatePosition(player.getPosition());
    
    

    
    

    // Calculate the offset to center the screen on the player
    int offsetX = SCREEN_WIDTH / 2 - player.getPosition().x;
    int offsetY = SCREEN_HEIGHT / 2 - player.getPosition().y;

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render background texture with camera offset
    SDL_Rect backgroundRect = { offsetX, offsetY, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

    // Render game objects with the calculated offset
    player.render(renderer, offsetX, offsetY);
    enemy.render(renderer, offsetX, offsetY);

	// Update and render the projectile
    player.getProjectile().update();
    player.getProjectile().render(renderer, offsetX, offsetY);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Check player's health
    if (player.getHealth() <= 0) {
        quit = true;  // Exit the game if the player's health reaches 0
    }

    // Cap the frame rate to approximately 60 frames per second
    Uint32 currentTime = SDL_GetTicks();
    Uint32 deltaTime = currentTime - lastFrameTime;

    if (deltaTime < 16) {
        SDL_Delay(16 - deltaTime);  // Cap the frame rate
    }

    lastFrameTime = currentTime;
}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

