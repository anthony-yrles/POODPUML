#include "./ModelH/Entity.h"

Entity::Entity(SDL_Renderer* renderer, int x, int y, int width, int height, const char* image) : 
    renderer(renderer), x(x), y(y), width(width), height(height), image(image) {}

int Entity::getEntityX() const {
    return x;
}

void Entity::setEntityX(int x) {
    this->x = x;
}

int Entity::getEntityY() const {
    return y;
}

void Entity::setEntityY(int y) {
    this->y = y;
}

int Entity::getEntityWidth() const {
    return width;
}

void Entity::setEntityWidth(int width) {
    this->width = width;
}

int Entity::getEntityHeight() const {
    return height;
}

void Entity::setEntityHeight(int height) {
    this->height = height;
}

const char* Entity::getEntityImage() const {
    return image;
}

void Entity::setEntityImage(const char* image) {
    this->image = image;
}

void Entity::drawEntity(Draw* draw) {
    draw->drawImage(renderer, x, y, width, height, image);
}