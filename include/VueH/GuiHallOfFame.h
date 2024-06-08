#pragma once
#include "./ControllerH/HofController.h"
#include "./VueH/Draw.h"

class GuiHallOfFame {
public:
    GuiHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/);
    ~GuiHallOfFame();

    bool drawHallOfFame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
private:

    SDL_Window* hallOfFameWindow;
    SDL_Renderer* hallOfFameRenderer;
    int WIDTH, HEIGHT;
    int mouseX, mouseY;
    bool clicked;
    bool running;
    HofController hofController;
}; 