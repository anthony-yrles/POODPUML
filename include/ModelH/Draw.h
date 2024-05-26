// Last update: 22:00 11.05.2020
#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <functional>

using namespace std;

class Draw {
    
    // The Draw class is responsible for drawing rectangles, images and text on the screen.
    // It also creates buttons that can be clicked.
    
public:
    explicit Draw(SDL_Renderer* renderer, bool clicked);

    void drawRect(int x, int y, int width, int height, int r, int g, int b, int a);
    void drawImage(int x, int y, int width, int height, const char* image);
    void drawText(int x, int y, const char* text, int r, int g, int b, int a);
    void createButton(int x, int y, int width, int height, const char* image, int mouseX, int mouseY, bool clicked, std::function<void()> onClick);

private:
    SDL_Renderer* renderer;
    bool clicked;
};

#endif // DRAW_H
