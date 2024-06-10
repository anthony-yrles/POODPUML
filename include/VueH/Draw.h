#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

class Draw {
    
    // The Draw class is responsible for drawing rectangles, images, and text on the screen.
    // It also creates buttons that can be clicked.
    
public:
    // Constructor
    explicit Draw(bool clicked);

    // Create SDL window
    SDL_Window* createWindow(int WIDTH, int HEIGHT, const char *title, SDL_Window* name);
    // Create SDL renderer
    SDL_Renderer* createRenderer(SDL_Window* name, SDL_Renderer* rendererName);
    // Draw filled rectangle
    void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height, int r, int g, int b, int a);
    // Draw image
    void drawImage(SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);
    // Draw text
    void drawText(SDL_Renderer* renderer, int x, int y, const char* text, int r, int g, int b, int a, int size);
    // Create clickable button
    void createButton(SDL_Renderer* renderer, int x, int y, int width, int height, const char* image, int mouseX, int mouseY, bool clicked, std::function<void()> onClick);

private:
    bool clicked; // Flag indicating if the button is clicked
};
