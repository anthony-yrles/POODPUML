#pragma once
#include "./ControllerH/HofController.h"
#include "./VueH/Draw.h"

class GuiHallOfFame : public Observer {
public:
    GuiHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/);
    ~GuiHallOfFame();

    bool drawHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
    int returnDifficulty(Draw draw, SDL_Renderer* hallOfFameRenderer, int mouseX, int mouseY, bool clicked);
    void drawData(int difficultyHof, Draw draw, SDL_Renderer* hallOfFameRenderer, HofController hofController);
    void update() override;

private:
    SDL_Window* hallOfFameWindow;
    SDL_Renderer* hallOfFameRenderer;

    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool clicked;
    bool running;
    int difficultyHof;

    HofController hofController;
}; 