#ifndef GUI_MENU_H
#define GUI_MENU_H

#include "Draw.h"

class GuiMenu {
    public:
        GuiMenu(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Window* window, int WIDTH, int HEIGHT, bool clicked, bool running, SDL_Event evenement);

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

#endif // GUI_MENU_H