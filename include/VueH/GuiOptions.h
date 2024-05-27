#ifndef GUI_OPTIONS_H
#define GUI_OPTIONS_H

#include ".\VueH\CreateFromJson.h"
#include <sstream>
#include <vector>

class GuiOptions {
    public:
        GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running);

        bool drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running);
        
    private:
        int WIDTH, HEIGHT;
        int mouseX, mouseY;
        bool clicked;
        bool running;
        SDL_Event evenement;
        SDL_Window* optionsWindow;
        SDL_Renderer* optionsRenderer;
};

#endif // GUI_OPTIONS_H