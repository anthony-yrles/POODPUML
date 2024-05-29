#pragma once

#include <.\VueH\Draw.h>
#include <./ControllerH/MapController.h>

class GuiInGame {
    public:
        GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    
        bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
        void tileSize (int WIDTH, int HEIGHT, int filewidth, int fileheight);
        void drawMap(const string& filename, SDL_Renderer* gameRenderer, int x, int y, int fileHeight, int fileWidth, Draw* draw);

    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        int tileWidth, tileHeight;
        int beginX, beginY;
        bool clicked;
        bool running;
        vector<vector<Tile>> tiles;

        SDL_Event evenement;
        SDL_Window* gameWindow;
        SDL_Renderer* gameRenderer;
};