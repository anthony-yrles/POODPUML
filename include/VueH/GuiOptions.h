#pragma once

#include <.\VueH\Draw.h> // Including the Draw header file from the VueH directory
#include "ControllerH/OptionController.h" // Including the OptionController header file from the ControllerH directory
#include "VueH/GuiMenu.h" // Including the GuiMenu header file from the VueH directory

class GuiOptions {
public:
    // Constructor
    GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running);

    // Method to draw the options interface
    bool drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer);
    
    // Method to draw the volume control rectangle
    void rectVolume(SDL_Renderer* renderer, int x, int y, int width, int height, int currentVolume, int maxVolume, Draw* draw);
    
    // Method to handle difficulty selection
    void difficultyChoice(Draw draw, SDL_Renderer* optionRenderer, OptionController* optionController, int mouseX, int mouseY, bool clicked);

private:
    int WIDTH, HEIGHT; // Width and height of the window
    int mouseX, mouseY; // Mouse position
    bool clicked; // Flag indicating if the mouse button is clicked
    bool running; // Flag indicating if the program is running

    SDL_Event evenement; // SDL event object for event handling
};