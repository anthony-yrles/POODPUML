#pragma once

#include <SDL2/SDL.h>
#include "./VueH/Draw.h"

/**
 * @class Entity
 * @brief Represents a generic game entity.
 *
 * The Entity class provides basic functionalities for game entities,
 * including position, dimensions, and rendering.
 */
class Entity {
public:
    /**
     * @brief Constructs an Entity object.
     * @param renderer Pointer to the SDL renderer used to draw the entity.
     * @param x Initial x position of the entity.
     * @param y Initial y position of the entity.
     * @param width Width of the entity.
     * @param height Height of the entity.
     * @param image Path to the entity's texture image.
     */
    Entity(SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    /**
     * @brief Gets the current x position of the entity.
     * @return Current x position of the entity.
     */
    float getEntityX() const;

    /**
     * @brief Sets the x position of the entity.
     * @param x New x position of the entity.
     */
    void setEntityX(float x);

    /**
     * @brief Gets the current y position of the entity.
     * @return Current y position of the entity.
     */
    float getEntityY() const;

    /**
     * @brief Sets the y position of the entity.
     * @param y New y position of the entity.
     */
    void setEntityY(float y);

    /**
     * @brief Gets the current width of the entity.
     * @return Current width of the entity.
     */
    int getEntityWidth() const;

    /**
     * @brief Sets the width of the entity.
     * @param width New width of the entity.
     */
    void setEntityWidth(int width);

    /**
     * @brief Gets the current height of the entity.
     * @return Current height of the entity.
     */
    int getEntityHeight() const;

    /**
     * @brief Sets the height of the entity.
     * @param height New height of the entity.
     */
    void setEntityHeight(int height);

    /**
     * @brief Gets the image path of the entity.
     * @return Image path of the entity.
     */
    const char* getEntityImage() const;

    /**
     * @brief Sets the image path of the entity.
     * @param image New image path of the entity.
     */
    void setEntityImage(const char* image);

    /**
     * @brief Draws the entity using the provided Draw utility.
     * @param draw Pointer to the Draw utility class.
     */
    void drawEntity(Draw* draw);

protected:
    SDL_Renderer* renderer; ///< SDL renderer used to draw the entity.
    float x, y; ///< Current x and y position of the entity.
    int width, height; ///< Width and height of the entity.
    const char* image; ///< Path to the entity's texture image.
};
