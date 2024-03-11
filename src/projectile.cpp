#include "projectile.h"

Projectile::Projectile(b2World* world, SDL_Renderer* renderer, const std::string& imagePath, float x, float y, float width, float height)
    : world(world),
      body(nullptr),
      texture(nullptr),
      alive(true) ,
      position({0, 0}),
      width(width),
      height(height){

    texture = loadTexture(renderer, imagePath);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PPM, y / PPM);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2 / PPM, height / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Projectile::~Projectile() {
    //SDL_DestroyTexture(texture);
    //world->DestroyBody(body);
}

void Projectile::setVelocityX(float vx) {
    velocity.x = vx;
}

void Projectile::setVelocityY(float vy) {
    velocity.y = vy;
}

void Projectile::update() {

    body->SetLinearVelocity(velocity);

    position.x = static_cast<int>(body->GetPosition().x * PPM);
    position.y = static_cast<int>(body->GetPosition().y * PPM);

    alive = isAlive();
}

void Projectile::render(SDL_Renderer* renderer, int offsetX, int offsetY) const {
    //SDL_Rect renderPosition = position;
    SDL_Rect renderPosition = {
       static_cast<int>(position.x) + offsetX,
       static_cast<int>(position.y) + offsetY,
       static_cast<int>(width * PPM),
       static_cast<int>(height * PPM)
    };
SDL_RenderCopy(renderer, texture, nullptr, &renderPosition);
printf("Rendering projectile at (%d, %d)\n", renderPosition.x, renderPosition.y);
}


SDL_Rect Projectile::getPosition() const {
    return position;
}


SDL_Texture* Projectile::loadTexture(SDL_Renderer* renderer, const std::string& path) {
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
    } else {
        printf("Texture loaded successfully: %s\n", path.c_str());
    }

    return texture;
}


bool Projectile::isAlive() const {
    return position.x >= 0 && position.y >= 0 && position.x <= SCREEN_WIDTH && position.y <= SCREEN_HEIGHT;
}


