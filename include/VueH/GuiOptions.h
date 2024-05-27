#ifndef GUI_OPTIONS_H
#define GUI_OPTIONS_H

#include ".\VueH\Draw.h"
#include <sstream>
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

#endif // GUI_OPTIONS_H