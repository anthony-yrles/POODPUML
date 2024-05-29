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

    drawMap("./assets/map/map.txt", gameRenderer, WIDTH -300, HEIGHT, 0, 0, &draw);
    SDL_RenderPresent(gameRenderer);
    }
    return running;
}

void GuiInGame::drawMap(const string& filename, SDL_Renderer* gameRenderer, int width, int height, int fileHeight, int fileWidth, Draw* draw) {
    MapController mapController;
    Map map(width, height, fileHeight, fileWidth, filename);
    map.searchFileWidthHeight(filename);
    vector<vector<Tile>> tiles = mapController.createAndReturnMap(filename, &map);


    for (long long unsigned int i = 0; i < tiles.size(); ++i) {
        for (long long unsigned int j = 0; j < tiles[i].size(); ++j) {

            if (tiles[i][j].isEmpty) {
                draw->drawRect(gameRenderer, j * 32, i * 32, 32, 32, 0, 255, 0, 255);
            } else if (tiles[i][j].isMonsterPath) {
                draw->drawRect(gameRenderer, j * 32, i * 32, 32, 32, 0, 0, 255, 255);
            } else if (tiles[i][j].isMonsterBegin || tiles[i][j].isMonsterEnd) {
                draw->drawRect(gameRenderer, j * 32, i * 32, 32, 32, 255, 0, 0, 255);
            } else if (tiles[i][j].isTowerEmplacement) {
                draw->drawRect(gameRenderer, j * 32, i * 32, 32, 32, 0, 0, 255, 255);
            } else if (tiles[i][j].isDecoration) {
                draw->drawRect(gameRenderer, j * 32, i * 32, 32, 32, 255, 255, 0, 255);
            }
        }
    }
}