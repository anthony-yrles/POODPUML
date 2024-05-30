#pragma once

#include <vector>
#include "./VueH/Draw.h"
#include "./ControllerH/MapController.h"

class GuiInGame {
public:
    GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);

    bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    void tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight);
    void drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController);
    void drawEnemy(Map* map, MapController* mapController, Draw* draw, const string& filename, int enemyNumber, int width, int height, SDL_Renderer* gameRenderer);

private:
    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    int tileWidth, tileHeight;
    int beginX, beginY;
    int enemySpawned = 0;
    bool clicked;
    bool running;
    vector<vector<Tile>> tiles;

    SDL_Event evenement;
    SDL_Window* gameWindow;
    SDL_Renderer* gameRenderer;
};
