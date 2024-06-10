#pragma once

#include <vector>
#include "./VueH/Draw.h"
#include "./ControllerH/MapController.h"
#include "./ControllerH/HofController.h"
#include "./ControllerH/OptionController.h"

class GuiInGame {
public:
    // Constructor
    GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    
    // Method to draw the in-game interface
    bool drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    
    // Method to draw the game map
    void drawMap(const string& filename, Map* map, Draw* draw, int width, int height, SDL_Renderer* gameRenderer, MapController* mapController, OptionController* optionController, int mouseX, int mouseY, bool clicked);
    
    // Method to draw the in-game menu
    void drawMenuInGame(Draw* draw, MapController* mapcontroller, SDL_Renderer* gameRenderer, int width, int height, int mouseX, int mouseY, bool clicked, int level, int difficulty);
    
    // Method to draw the victory screen
    void drawVictory(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController);
    
    // Method to draw the defeat screen
    void drawDefeat(SDL_Renderer* gameRenderer, Draw* draw, int width, int height, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController);
    
    // Method to draw the keyboard
    void drawKeyboard(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController);
    
    // Method to draw the options interface
    void drawOption(SDL_Renderer* gameRenderer, Draw* draw, int mouseX, int mouseY, bool clicked, MapController* mapController, OptionController* optionController);

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
    HofController hofController;
};