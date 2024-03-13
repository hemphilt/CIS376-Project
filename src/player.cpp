#include "player.h"


// Define a map to store user data associated with player bodies
std::map<b2Body*, EntityUserData*> playerUserDataMap;


Player::Player(PhysicsWorld* physics, b2World* world, SDL_Renderer* renderer, const std::string& imagePath, int x, int y, int width, int height)
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
    body = physics.addBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2 / PPM, height / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetLinearVelocity(b2Vec2(0, 0));

    health = 100;
    mana = 50;
    playerClass = "Warrior";
    
      body->CreateFixture(&fixtureDef);
    
     // Set user data for the player body
    EntityUserData* playerUserData = new EntityUserData{EntityUserData::PLAYER};

    // Add the player to the map
    playerUserDataMap[body] = playerUserData;
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

void Player::handleInput(SDL_Renderer* renderer, const Uint8* currentKeyStates) {
    b2Vec2 velocity(0, 0);

    if (currentKeyStates[SDL_SCANCODE_W]) {
        velocity.y = -PLAYER_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        velocity.y = PLAYER_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        velocity.x = -PLAYER_SPEED;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        velocity.x = PLAYER_SPEED;
    }

    // Set the velocity directly
    body->SetLinearVelocity(velocity);

    // Check right-click to shoot
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        shootProjectile(renderer);
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
    // Check if enough time has passed since the last shot
    Uint32 currentTime = SDL_GetTicks();
    if (static_cast<Uint32>(currentTime) - static_cast<Uint32>(lastShotTime) < static_cast<Uint32>(shotCooldown)) {
        return; // Shot on cooldown
    }

    // Calculate the initial position for the projectile (right middle side of the player)
    b2Vec2 playerPosition = body->GetPosition();
    float playerWidth = 16 / PPM; // Adjust with the actual player width
    float playerHeight = 32 / PPM; // Adjust with the actual player height
    float initialX = playerPosition.x + (playerWidth / 2.0f);
    float initialY = playerPosition.y + (playerHeight / 2.0f);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Calculate the mouse direction relative to the player's position
    b2Vec2 mouseDirection(mouseX / PPM - initialX, mouseY / PPM - initialY);
    mouseDirection.Normalize();

    // Create and set up the new projectile
    Projectile newProjectile(
        world,
        renderer,
        "./assets/arrow.png",
        initialX * PPM,
        initialY * PPM,
        10 / PPM,
        10 / PPM
    );

    const float projectileSpeed = 5.0f;
    newProjectile.setVelocityX(mouseDirection.x * projectileSpeed);
    newProjectile.setVelocityY(mouseDirection.y * projectileSpeed);

    // Add the new projectile to the vector
    projectiles.push_back(newProjectile);

    // Update the last shot time
    lastShotTime = currentTime;
}


void Player::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect playerRect = {
        static_cast<int>((body->GetPosition().x * PPM) + offsetX),
        static_cast<int>((body->GetPosition().y * PPM) + offsetY),
        static_cast<int>(16 / PPM * PPM),
        static_cast<int>(32 / PPM * PPM)
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


void Player::handleBeginContact(EntityUserData* otherUserData) {
    if (otherUserData && otherUserData->type == EntityUserData::ENEMY) {
        health -= 10;
        printf("Player Health: %d\n", health); //Debug Print
    }
}
