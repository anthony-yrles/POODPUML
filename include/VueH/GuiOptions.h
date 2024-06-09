#pragma once

#include <.\VueH\Draw.h>
#include "ControllerH/OptionController.h"
#include <vector>

class GuiOptions {
    public:
        GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running);

        bool drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer);
        
    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;
        SDL_Event evenement;
};