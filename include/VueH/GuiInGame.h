#pragma once

#include <vector>
#include "./VueH/Draw.h"
#include "./ControllerH/MapController.h"

class GuiInGame {
public:
    GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);

    bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    void drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, int mouseX, int mouseY, bool clicked);
    void drawMenuInGame(Draw* draw, SDL_Renderer* gameRenderer, int width, int height, const char* textTitre, const char* textTotalEnemies, const char* textEnemiesLeft, const char* goldEarn, const char* towerCost, int mouseX, int mouseY, bool clicked);

private:
    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool clicked;
    bool running;

    SDL_Event evenement;
    SDL_Window* gameWindow;
    SDL_Renderer* gameRenderer;
};
