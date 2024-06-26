#pragma once

#include <.\VueH\Draw.h>

class GuiMenu {
public:
    // Constructor
    GuiMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event evenement);
    // Draw menu interface
    bool drawMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event evenement);
        
private:
    SDL_Renderer* renderer;
    int mouseX, mouseY;
    SDL_Window* window;
    int WIDTH, HEIGHT;
    bool clicked;
    bool running;
    SDL_Event evenement;
};
