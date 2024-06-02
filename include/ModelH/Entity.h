#pragma once

#include <SDL2/SDL.h>
#include "./VueH/Draw.h"

class Entity {
public:
    Entity(SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);

    int getEntityX() const;
    void setEntityX(int x);

    int getEntityY() const;
    void setEntityY(int y);

    int getEntityWidth() const;
    void setEntityWidth(int width);

    int getEntityHeight() const;
    void setEntityHeight(int height);

    const char* getEntityImage() const;
    void setEntityImage(const char* image);

    void drawEntity(Draw* draw);

protected:
    SDL_Renderer* renderer;
    int x, y, width, height;
    const char* image;
};