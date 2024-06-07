#pragma once

#include <vector>
#include "./VueH/Draw.h"
#include "./ControllerH/MapController.h"

class GuiInGame {
public:
    GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);

    bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    void drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, int mouseX, int mouseY, bool clicked);
    void drawMenuInGame(Draw* draw, MapController* mapcontroller, SDL_Renderer* gameRenderer, int width, int height, int mouseX, int mouseY, bool clicked, int level, int difficulty);
    void drawVictory(SDL_Renderer* gameRenderer, Draw* draw, int width, int height);
    void drawDefeat(SDL_Renderer* gameRenderer, Draw* draw, int width, int height);

private:
    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool clicked;
    bool running;
    bool gameDebut = false;
    bool attributesChanged = false;
    bool victory = false;
    bool defeat = false;

    SDL_Event evenement;
    SDL_Window* gameWindow;
    SDL_Renderer* gameRenderer;
};
