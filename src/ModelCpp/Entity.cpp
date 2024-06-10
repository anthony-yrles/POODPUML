#include "./ModelH/Entity.h"

/**
 * @brief Constructs an Entity object with the specified parameters.
 * @param renderer Pointer to the SDL renderer used to draw the entity.
 * @param x Initial x position of the entity.
 * @param y Initial y position of the entity.
 * @param width Width of the entity.
 * @param height Height of the entity.
 * @param image Path to the entity's texture image.
 */
Entity::Entity(SDL_Renderer* renderer, float x, float y, int width, int height, const char* image) : 
    renderer(renderer), x(x), y(y), width(width), height(height), image(image) {}

/**
 * @brief Gets the current x position of the entity.
 * @return Current x position of the entity.
 */
float Entity::getEntityX() const {
    return x;
}

/**
 * @brief Sets the x position of the entity.
 * @param x New x position of the entity.
 */
void Entity::setEntityX(float x) {
    this->x = x;
}

/**
 * @brief Gets the current y position of the entity.
 * @return Current y position of the entity.
 */
float Entity::getEntityY() const {
    return y;
}

/**
 * @brief Sets the y position of the entity.
 * @param y New y position of the entity.
 */
void Entity::setEntityY(float y) {
    this->y = y;
}

/**
 * @brief Gets the current width of the entity.
 * @return Current width of the entity.
 */
int Entity::getEntityWidth() const {
    return width;
}

/**
 * @brief Sets the width of the entity.
 * @param width New width of the entity.
 */
void Entity::setEntityWidth(int width) {
    this->width = width;
}

/**
 * @brief Gets the current height of the entity.
 * @return Current height of the entity.
 */
int Entity::getEntityHeight() const {
    return height;
}

/**
 * @brief Sets the height of the entity.
 * @param height New height of the entity.
 */
void Entity::setEntityHeight(int height) {
    this->height = height;
}

/**
 * @brief Gets the image path of the entity.
 * @return Image path of the entity.
 */
const char* Entity::getEntityImage() const {
    return image;
}

/**
 * @brief Sets the image path of the entity.
 * @param image New image path of the entity.
 */
void Entity::setEntityImage(const char* image) {
    this->image = image;
}

/**
 * @brief Draws the entity using the provided Draw utility.
 * @param draw Pointer to the Draw utility class.
 */
void Entity::drawEntity(Draw* draw) {
    draw->drawImage(renderer, x, y, width, height, image);
}