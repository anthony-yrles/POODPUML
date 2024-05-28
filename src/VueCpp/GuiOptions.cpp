#include ".\VueH\GuiOptions.h"

GuiOptions::GuiOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running){
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

bool GuiOptions::drawOptions(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Window* optionWindow, SDL_Renderer* optionRenderer) {

    Draw draw(clicked);
    optionWindow = draw.createWindow(WIDTH, HEIGHT, "Options", optionWindow);
    optionRenderer = draw.createRenderer(optionWindow, optionRenderer);

    CreateFromJson createFromJson;
    json jsonData = createFromJson.readJsonFile("./assets/draw.json");

    // Option loop
    while (!running) {
        // Event handling
        while (SDL_PollEvent(&evenement) != 0) {
            if (evenement.type == SDL_QUIT) {
                running = true;
                return running;
            } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                clicked = true;
                SDL_GetMouseState(&mouseX, &mouseY);
            } else if (evenement.type == SDL_MOUSEBUTTONUP) {
                clicked = false;
            }
        }
    createFromJson.readOptions(jsonData, Draw(), optionRenderer, mouseX, mouseY, clicked, optionWindow, running, WIDTH, HEIGHT);   
    SDL_RenderPresent(optionRenderer);
    }

    // Destroy the optionRenderer
    SDL_DestroyRenderer(optionRenderer);
    // Destroy the optionWindow
    SDL_DestroyWindow(optionWindow);
    // Quit SDL
    SDL_Quit();

    return running;
}