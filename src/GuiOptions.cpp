#include "GuiOptions.h"

GuiOptions::GuiOptions(int mouseX, int mouseY, int WIDTH, int HEIGHT, bool clicked) {
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->clicked = clicked;
}

void GuiOptions::drawOptions(int mouseX, int mouseY, int WIDTH, int HEIGHT, bool clicked) {

    // Create a new window
    SDL_Window* option_window = SDL_CreateWindow("Options", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    // Error handling
    if (!option_window) {
        cerr << "Erreur lors de la création de la fenêtre: " << SDL_GetError();
        SDL_Quit();
        return;
    }

    // Create a renderer
    SDL_Renderer* optionRenderer = SDL_CreateRenderer(option_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Error handling
    if (!optionRenderer) {
        cerr << "Erreur lors de la création du renderer: " << SDL_GetError();
        SDL_DestroyWindow(option_window);
        SDL_Quit();
        return;
    }

    // Create a Draw object
    Draw draw(optionRenderer, clicked);

    // Clear the renderer
    SDL_RenderClear(optionRenderer);

    // Using of the drawImage method from the Draw class to draw the background
    draw.drawImage(0, 0, 1200, 600, "./assets/images/bcgOption.png");

    draw.drawImage(-100, -50, 1400, 750, "./assets/images/settings.png");

    SDL_RenderPresent(optionRenderer);

}