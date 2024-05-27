#include "./VueH/GuiInGame.h"

GuiInGame::GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement){
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->clicked = clicked;
    this->running = running;
}

bool GuiInGame::drawInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event evenement) {

    // Create a Draw object
    Draw draw(clicked);
    gameWindow = draw.createWindow(WIDTH, HEIGHT, "Game", gameWindow);
    gameRenderer = draw.createRenderer(gameWindow, gameRenderer);

    // Game loop
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

    // Clear the renderer
    SDL_RenderClear(gameRenderer);

    }
    return running;
}
