#pragma once
#include <.\VueH\Draw.h>
#include "ControllerH/OptionController.h"

class GuiOptions {
    public:
        GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running);

        bool drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer);
        void rectVolume(SDL_Renderer* renderer, int x, int y, int width, int height, int currentVolume, int maxVolume, Draw* draw);
        void difficultyChoice(Draw draw, SDL_Renderer* optionRenderer, OptionController* optionController, int mouseX, int mouseY, bool clicked);

    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;

        SDL_Event evenement;
};