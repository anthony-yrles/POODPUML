#ifndef INGAME_H
#define INGAME_H

#include "./VueH/CreateFromJson.h"

class GuiInGame {
    public:
        GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    
        bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);

    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;
        SDL_Event evenement;
        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;
};

#endif // INGAME_H