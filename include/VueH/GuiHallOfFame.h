#pragma once
#include "./ControllerH/HofController.h"
#include "./VueH/Draw.h"
#include "VueH/GuiMenu.h"

class GuiHallOfFame : public Observer {
public:
    // Constructor
    GuiHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/);
    // Destructor
    ~GuiHallOfFame();

    // Draw Hall of Fame interface
    bool drawHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    // Return selected difficulty
    int returnDifficulty(Draw draw, SDL_Renderer* hallOfFameRenderer, int mouseX, int mouseY, bool clicked);
    // Draw Hall of Fame data
    void drawData(int difficultyHof, Draw draw, SDL_Renderer* hallOfFameRenderer, HofController hofController);
    // Update method from Observer interface
    void update() override;

private:
    SDL_Window* hallOfFameWindow;
    SDL_Renderer* hallOfFameRenderer;

    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool clicked;
    bool running;
    int difficultyHof;

    HofController hofController; // Controller for Hall of Fame data
}; 