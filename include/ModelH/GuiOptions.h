#ifndef GUI_OPTIONS_H
#define GUI_OPTIONS_H

#include ".\ModelH\Draw.h"
#include <sstream>
#include <vector>

class GuiOptions {
    public:
        GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);

        bool drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement);
        
    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;
        SDL_Event evenement;
};

#endif // GUI_OPTIONS_H