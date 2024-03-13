#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <chrono>
#include <box2d/box2d.h>
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "/home/hemphito/CIS376/CIS376-Project/include/physics.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define PPM 100.0f

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* backgroundImage = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "main",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Load background image
    backgroundImage = IMG_Load("./assets/dungeon.png");
    if (backgroundImage == nullptr) {
        std::cerr << "Could not load image: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create texture from the surface
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
    if (backgroundTexture == nullptr) {
        std::cerr << "Could not create background texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(backgroundImage);
        return 1;
    }

    // Free the surface as it is no longer needed
    SDL_FreeSurface(backgroundImage);
    backgroundImage = nullptr;

    // Create a Box2D world
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);
    
    PhysicsWorld physics(b2Vec2(0.0, -10.0f));
    

    
    	b2BodyDef groundDef;
	groundDef.position.Set(0, 0);
	groundDef.type=b2_staticBody;
	b2Body* ground = physics.addBody(&groundDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(8.0f, 10.0f);
	ground->CreateFixture(&groundBox, 1.0f);


	b2BodyDef leftDef;
	leftDef.position.Set(0, 3);
	leftDef.type=b2_staticBody;
	b2Body* left = physics.addBody(&leftDef);
	b2PolygonShape leftBox;
	leftBox.SetAsBox(10.0f, 8.0f);
	left->CreateFixture(&leftBox, 1.0f);

	b2BodyDef rightDef;
	rightDef.position.Set(0, 10);
	rightDef.type=b2_staticBody;
	b2Body* right = physics.addBody(&rightDef);
	b2PolygonShape rightBox;
	rightBox.SetAsBox(10.0f, 8.0f);
	right->CreateFixture(&rightBox, 1.0f);
    
    
    

    // Create a Player
    Player player(&physics, &world, renderer, "./assets/warrior.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, 32);

    // Create an Enemy on the other side of the screen
    Enemy enemy(&world, renderer, "./assets/skeleton.png", SCREEN_WIDTH - 100, 100, 16, 32);

    // Main game loop
    bool quit = false;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    auto lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;

    while (!quit) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = currentTime - lastTime;
        deltaTime = duration.count();
        lastTime = currentTime;
        
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        player.handleInput(renderer, currentKeyStates);

        enemy.update(player.getBody()->GetPosition().x * PPM, player.getBody()->GetPosition().y * PPM, deltaTime);


        int offsetX = SCREEN_WIDTH / 2 - static_cast<int>(player.getBody()->GetPosition().x * PPM);
        int offsetY = SCREEN_HEIGHT / 2 - static_cast<int>(player.getBody()->GetPosition().y * PPM);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        SDL_Rect backgroundRect = { offsetX, offsetY, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, &backgroundRect);

        player.render(renderer, offsetX, offsetY);
        enemy.render(renderer, offsetX, offsetY);

        std::vector<Projectile> aliveProjectiles;

        for (auto& projectile : player.getProjectiles()) {
            projectile.render(renderer, offsetX, offsetY);
            projectile.update();

            if (projectile.isAlive()) {
                aliveProjectiles.push_back(projectile);
            }
        }

        player.setProjectiles(aliveProjectiles);

        SDL_RenderPresent(renderer);

        if (player.getHealth() <= 0) {
            quit = true;
        }

        world.Step(1.0f / 60.0f, 6, 2);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

