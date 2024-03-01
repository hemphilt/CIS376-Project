#include "player.h"
#include "projectile.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define PLAYER_SPEED 2.0f
#define PPM 32.0f

Player::Player(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
    : world(world),
      body(nullptr),
      projectiles(),
      lastShotTime(0),
      shotCooldown(1000) {

    texture = loadTexture(renderer, imagePath);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PPM, y / PPM);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2 / PPM, height / 2 / PPM);  // Divide by PPM to set the size in Box2D units

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    health = 100;
    mana = 50;
    playerClass = "Warrior";
}

Player::~Player() {
    SDL_DestroyTexture(texture);
    world->DestroyBody(body);
}

void Player::setPosition(float x, float y) {
    body->SetTransform(b2Vec2(x / PPM, y / PPM), body->GetAngle());
}

b2Body* Player::getBody() const {
    return body;
}

void Player::handleInput(const Uint8* currentKeyStates) {
    b2Vec2 velocity(0, 0);

    if (currentKeyStates[SDL_SCANCODE_W]) {
        velocity.y = -PLAYER_SPEED / PPM;  // Convert speed to Box2D units
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        velocity.y = PLAYER_SPEED / PPM;  // Convert speed to Box2D units
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        velocity.x = -PLAYER_SPEED / PPM;  // Convert speed to Box2D units
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        velocity.x = PLAYER_SPEED / PPM;  // Convert speed to Box2D units
    }

    // Reset velocity if no keys are pressed
    if (!currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_S]) {
        velocity.y = 0;
    }
    if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D]) {
        velocity.x = 0;
    }

    body->SetLinearVelocity(velocity);

    // Check right-click to shoot
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        shootProjectile(nullptr); // Passing nullptr as renderer, adjust as needed
    }
}

SDL_Texture* Player::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        fprintf(stderr, "Error loading image %s: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (texture == nullptr) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void Player::shootProjectile(SDL_Renderer* renderer) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    b2Vec2 playerPosition = body->GetPosition();
    b2Vec2 mouseDirection(mouseX / PPM - playerPosition.x * PPM, mouseY / PPM - playerPosition.y * PPM);
    mouseDirection.Normalize();

    Projectile newProjectile(world, renderer, "./assets/arrow.png", playerPosition.x * PPM, playerPosition.y * PPM, 10, 10);

    const float projectileSpeed = 5.0f;
    newProjectile.setVelocityX(mouseDirection.x * projectileSpeed);
    newProjectile.setVelocityY(mouseDirection.y * projectileSpeed);

    projectiles.push_back(newProjectile);
    lastShotTime = SDL_GetTicks();
}

void Player::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect playerRect = {
        static_cast<int>((body->GetPosition().x * PPM) + offsetX),
        static_cast<int>((body->GetPosition().y * PPM) + offsetY),
        static_cast<int>(25 / PPM * PPM),
        static_cast<int>(50 / PPM * PPM)
    };
    SDL_RenderCopy(renderer, texture, nullptr, &playerRect);

    for (const auto& projectile : projectiles) {
        projectile.render(renderer, offsetX, offsetY);
    }
}
std::vector<Projectile>& Player::getProjectiles() {
    return projectiles;
}

void Player::setProjectiles(const std::vector<Projectile>& newProjectiles) {
    projectiles = newProjectiles;
}

int Player::getHealth() const {
    return health;
}

