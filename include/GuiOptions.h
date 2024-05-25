#ifndef GUI_OPTIONS_H
#define GUI_OPTIONS_H

#include "Draw.h"

class GuiOptions {
    public:
        GuiOptions(int mouseX, int mouseY, int WIDTH, int HEIGHT, bool clicked);

        void drawOptions(int mouseX, int mouseY, int WIDTH, int HEIGHT, bool clicked);
        
    private:
        int mouseX, mouseY;
        int WIDTH, HEIGHT;
        bool clicked;
};

#endif // GUI_OPTIONS_H