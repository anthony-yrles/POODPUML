#include "./VueH/GuiInGame.h"

GuiInGame::GuiInGame(int WIDTH, int HEIGHT, int mouseX, int mouseY, bool clicked, bool running, SDL_Event /*evenement*/) {
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
    drawMap("./assets/map/map.txt", gameRenderer, WIDTH -300, HEIGHT, &draw);

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

void GuiInGame::drawMap(const string& filename, SDL_Renderer* gameRenderer, int width, int height, Draw* draw) {
    // Créez le contrôleur de la carte et obtenez toutes les tuiles
    MapController mapController;
    Map map(width, height);
    std::vector<std::vector<Tile>> tiles = mapController.createAndReturnMap(filename, width, height, &map);

    // Parcourez les tuiles et dessinez-les
    for (long long unsigned int i = 0; i < tiles.size(); ++i) {
        for (long long unsigned int j = 0; j < tiles[i].size(); ++j) {
            if (tiles[i][j].isEmpty) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 0, 255, 0, 255);
            } else if (tiles[i][j].isMonsterPath) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 0, 0, 255, 255);
            } else if (tiles[i][j].isMonsterBegin) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 255, 0, 0, 255);
            } else if (tiles[i][j].isMonsterEnd) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 255, 0, 0, 255);
            } else if (tiles[i][j].isTowerEmplacement) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 0, 0, 255, 255);
            } else if (tiles[i][j].isDecoration) {
                draw->drawRect(gameRenderer, i * 32, j * 32, 32, 32, 255, 255, 0, 255);
            }
        }
    }
}