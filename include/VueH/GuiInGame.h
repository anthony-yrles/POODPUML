#pragma once

#include <.\VueH\Draw.h>
#include <./ControllerH/MapController.h>

class GuiInGame {
    public:
        GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    
        bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
        void drawMap(const string& filename, SDL_Renderer* gameRenderer, int x, int y, Draw* draw);

    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;
        vector<vector<Tile>> tiles;

        SDL_Event evenement;
        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;
};