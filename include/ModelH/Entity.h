#pragma once

#include <SDL2/SDL.h>
#include "./VueH/Draw.h"

class Entity {
public:
    Entity(SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);

    int getEntiryX() const;
    void setEntityX(int x);
    int getEntityY() const;
    void setEntityY(int y);
    int getEntiryWidth() const;
    void setEntityWidth(int width);
    int getEntiryHeight() const;
    void setEntityHeight(int height);
    const char* getEntiryImage() const;
    void setEntityImage(const char* image);

    void drawEntity(Draw* draw);

private:
    SDL_Renderer* renderer;
    int x;
    int y;
    int width;
    int height;
    const char* image;
};