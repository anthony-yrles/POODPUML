#pragma once

#include <SDL2/SDL.h>
#include "./VueH/Draw.h"

class Entity {
public:
    Entity(SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    float getEntityX() const;
    void setEntityX(float x);

    float getEntityY() const;
    void setEntityY(float y);

    int getEntityWidth() const;
    void setEntityWidth(int width);

    int getEntityHeight() const;
    void setEntityHeight(int height);

    const char* getEntityImage() const;
    void setEntityImage(const char* image);

    void drawEntity(Draw* draw);

protected:
    SDL_Renderer* renderer;
    float x, y;
    int width, height;
    const char* image;
};