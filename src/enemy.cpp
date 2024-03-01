#include "enemy.h"

Enemy::Enemy(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, float x, float y, float width, float height)
    : texture(nullptr),
      world(world),
      body(nullptr) {
    
    position.x = static_cast<int>(x);
    position.y = static_cast<int>(y);
    position.w = static_cast<int>(width);
    position.h = static_cast<int>(height);
    health = 100;
    enemyClass = "Warrior";

    texture = loadTexture(renderer, imagePath);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PPM, y / PPM);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(position.w / 2 / PPM, position.h / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
    world->DestroyBody(body);
}

SDL_Texture* Enemy::loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void Enemy::createBody(b2World* world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PPM, y / PPM);
    bodyDef.fixedRotation = true;  // Prevent player from rotating

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(position.w / 2 / PPM, position.h / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

void Enemy::render(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect renderPosition = position;
    renderPosition.x += offsetX;
    renderPosition.y += offsetY;
    SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
}

int Enemy::getHealth() const {
    return health;
}

std::string Enemy::getEnemyClass() const {
    return enemyClass;
}

void Enemy::setHealth(int newHealth) {
    health = newHealth;
}

void Enemy::setEnemyClass(const std::string& newEnemyClass) {
    enemyClass = newEnemyClass;
}

void Enemy::update(float playerX, float playerY, float deltaTime) {
    // Calculate the direction towards the player
    float deltaX = playerX - position.x;
    float deltaY = playerY - position.y;

    // Calculate the distance to the player
    float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    // Check if the player is within 300 pixels
    if (distance <= 300) {
        // Normalize the direction
        if (distance > 0) {
            deltaX = deltaX / distance * ENEMY_SPEED;
            deltaY = deltaY / distance * ENEMY_SPEED;
        }

        b2Vec2 velocity(deltaX, deltaY);

        // Normalize the vector only if the length exceeds 1
        if (velocity.LengthSquared() > 1.0f) {
            velocity.Normalize();
        }

        // Update the enemy position based on the calculated direction
        position.x += static_cast<int>(velocity.x * ENEMY_SPEED * deltaTime);
        position.y += static_cast<int>(velocity.y * ENEMY_SPEED * deltaTime);
    }

    // Additional update logic
}

const SDL_Rect Enemy::getPosition() const {
    return position;
}

void Enemy::setPosition(float x, float y) {
    body->SetTransform(b2Vec2(x / PPM, y / PPM), body->GetAngle());
}



